# ============================================================================#
#                                                                             #
# Ninja build target templates                                                #
#                                                                             #
# ============================================================================#

from os.path import join as pathjoin

from .config import DecompConfig
from .ninja_syntax import Writer
from .paths import Object, Batch, Library
from .utility import find_files


def target_reconfigure(writer: Writer, config: DecompConfig):
    """Emits a Ninja build target to re-run the configure script

    Args:
        writer (Writer): Ninja writer
        config (DecompConfig): Project configuration
    """

    # Reconfigure when ANY ninja-related script is changed
    ninja_files = find_files(
        pathjoin(config.tools_dir, "ninja"), [".py"])

    writer.comment("Re-run generator script")
    writer.build(
        outputs="$ninja_script",
        rule="reconfigure",
        implicit=["$configure", *ninja_files, DecompConfig.PATH],
    )
    writer.newline()


def target_compile(writer: Writer, config: DecompConfig, lib: Library,
                   obj: Object):
    """Emits a Ninja build target to compile the specified source file

    Args:
        writer (Writer): Ninja writer
        config (DecompConfig): Project configuration
        lib (Library): Parent library of this source file
        obj (Object): Source file
    """

    # Batch files define BATCH_* format macros for conditional compilation
    flags_str = " ".join(lib.flags())
    if type(obj) == Batch:
        flags_str = f"{flags_str} -D{obj.macro_name()}"

    # Batch files depend on included source files
    implicit = [DecompConfig.PATH]

    # Language standard flag
    if obj.is_cpp():
        flags_str = f"{flags_str} -std=gnu++11"
    else:
        flags_str = f"{flags_str} -std=gnu99"

    writer.comment(f"Compile {obj.path()}")
    writer.build(
        outputs=obj.base_object_path(),
        rule="compile",
        inputs=obj.path(),
        variables={
            "depfile": obj.dependency_path(),
            "cflags": flags_str,
        },
        implicit=implicit,
    )
    writer.newline()
