$sourceDir = "C:\Dev\ELFSplit\output_reassembly"
$outDir = "C:\Dev\ELFSplit\assembled_objs"
$clang = "C:\Program Files\LLVM\bin\clang.exe"

# Ensure output root exists
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

$sFiles = Get-ChildItem -Path $sourceDir -Recurse -Filter "*.s"
$total = $sFiles.Count
$succeeded = 0
$failed = @()

Write-Host "Assembling $total files..."

$i = 0
foreach ($f in $sFiles) {
    $i++
    if ($i % 100 -eq 0) {
        Write-Host "  Progress: $i / $total..."
    }

    # Get path relative to source directory manually
    $relativePath = $f.DirectoryName.Substring($sourceDir.Length).TrimStart('\', '/')
    
    $validSegments = @()
    if ($relativePath -ne "") {
        $segments = $relativePath -split "[\\/]"
        
        # Filter out single-child / redundant wrapper folders like 'mm', 'branch', 'world'
        # Keeps folders that actually contain files or branch out
        foreach ($seg in $segments) {
            # Skip generic single-layer wrapper directories if desired, 
            # or keep only the leaf folder name by clearing segments:
            # (To keep ONLY the final leaf folder name, uncomment the line below:)
            # $validSegments = @($segments[-1]); break;
            
            if ($seg -ne "mm" -and $seg -ne "branch" -and $seg -ne "world" -and $seg -ne "source" -and $seg -ne "project") {
                $validSegments += $seg
            }
        }
        
        # Fallback: if all segments were stripped, keep at least the immediate parent folder name
        if ($validSegments.Count -eq 0) {
            $validSegments = @($segments[-1])
        }
    }

    # Build target destination directory
    $destinationSubDir = $outDir
    foreach ($seg in $validSegments) {
        $destinationSubDir = Join-Path $destinationSubDir $seg
    }

    New-Item -ItemType Directory -Force -Path $destinationSubDir | Out-Null

    $objName = [System.IO.Path]::GetFileNameWithoutExtension($f.Name) + ".o"
    $objPath = Join-Path $destinationSubDir $objName

    # Run Clang compilation
    $result = & $clang --target=x86_64-unknown-linux-gnu -c $f.FullName -o $objPath 2>&1

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
    $failed | Export-Csv -Path "C:\Dev\ELFSplit\assembly_failures.csv" -NoTypeInformation
    Write-Host "`nFailure details written to assembly_failures.csv"
    Write-Host "`nFirst 10 failures:"
    $failed | Select-Object -First 10 | Format-Table -Wrap
}