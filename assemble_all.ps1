$baseDir = if ($PSScriptRoot) { $PSScriptRoot } else { (Get-Location).Path }

$sourceDir = Join-Path $baseDir "output_reassembly"
$outDir = Join-Path $baseDir "assembled_objs"
$csvPath = Join-Path $baseDir "assembly_failures.csv"

$clang = "clang"
if (-not (Get-Command $clang -ErrorAction SilentlyContinue)) {
    $clang = Join-Path $env:ProgramFiles "LLVM\bin\clang.exe"
    if (-not (Test-Path $clang)) {
        Write-Error "Clang not found. Please ensure LLVM is installed and in your system PATH."
        exit
    }
}

New-Item -ItemType Directory -Force -Path $outDir | Out-Null

if (-not (Test-Path $sourceDir)) {
    Write-Error "Source directory not found: $sourceDir"
    exit
}

$sFiles = Get-ChildItem -Path $sourceDir -Recurse -Filter "*.s"
$total = $sFiles.Count
$succeeded = 0
$failed = @()

Write-Host "Assembling $total files using portable paths and auto-patching..."

$i = 0
foreach ($f in $sFiles) {
    $i++
    if ($i % 100 -eq 0) {
        Write-Host "  Progress: $i / $total..."
    }

    $relativePath = $f.DirectoryName.Substring($sourceDir.Length).TrimStart('\', '/')
    
    $validSegments = @()
    if ($relativePath -ne "") {
        $segments = $relativePath -split "[\\/]"
        
        foreach ($seg in $segments) {
            if ($seg -ne "mm" -and $seg -ne "branch" -and $seg -ne "world" -and $seg -ne "source" -and $seg -ne "project") {
                $validSegments += $seg
            }
        }
        
        if ($validSegments.Count -eq 0) {
            $validSegments = @($segments[-1])
        }
    }

    $destinationSubDir = $outDir
    foreach ($seg in $validSegments) {
        $destinationSubDir = Join-Path $destinationSubDir $seg
    }

    New-Item -ItemType Directory -Force -Path $destinationSubDir | Out-Null

    $objName = [System.IO.Path]::GetFileNameWithoutExtension($f.Name) + ".o"
    $objPath = Join-Path $destinationSubDir $objName

    $result = & $clang --target=x86_64-unknown-linux-gnu -c $f.FullName -o $objPath 2>&1

    if ($LASTEXITCODE -ne 0) {
        $errString = $result -join " "
        if ($errString -match "Undefined temporary symbol") {
            $missingSymbols = [regex]::Matches($errString, '\.LC_[a-zA-Z0-9_]+') | ForEach-Object { $_.Value } | Select-Object -Unique

            if ($missingSymbols) {
                $content = Get-Content -Path $f.FullName -Raw
                
                foreach ($sym in $missingSymbols) {
                    $content += "`n${sym}:`n    .long 0`n"
                }

                $patchedPath = [System.IO.Path]::Combine([System.IO.Path]::GetTempPath(), $f.Name)
                Set-Content -Path $patchedPath -Value $content

                $result = & $clang --target=x86_64-unknown-linux-gnu -c $patchedPath -o $objPath 2>&1
                
                Remove-Item -Path $patchedPath -ErrorAction SilentlyContinue
            }
        }
    }

    if ($LASTEXITCODE -eq 0) {
        $succeeded++
    } else {
        $failed += [PSCustomObject]@{
            File = $f.FullName
            Error = ($result | Select-Object -First 3) -join " | "
        }
    }
}

Write-Host "`nDone: $succeeded/$total assembled successfully"
Write-Host "$($failed.Count) failed"

if ($failed.Count -gt 0) {
    $failed | Export-Csv -Path $csvPath -NoTypeInformation
    Write-Host "`nFailure details written to $csvPath"
    Write-Host "`nFirst 10 failures:"
    $failed | Select-Object -First 10 | Format-Table -Wrap
}