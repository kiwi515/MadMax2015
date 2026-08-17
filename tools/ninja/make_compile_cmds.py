#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Clangd compile_commands.json generator                                      #
#                                                                             #
# ============================================================================#

from json import dump
from os import getcwd
from os.path import abspath

from lib.config import DecompConfig
from lib.define import COMPILE_COMMANDS_NAME
from lib.paths import Object, Library, Batch
from master_object_layout import create_object_layout


def main():
    """Program entrypoint
    """

    config = DecompConfig.load()
    make_compile_cmds(config)


def make_compile_cmds(config: DecompConfig):
    """Creates the `compile_commands.json` file for the Clangd language
    parser
    """

    commands = []
    object_layout = create_object_layout(config)

    for lib in object_layout:
        for obj in lib.objects():
            commands.append(make_cmds_single(config, lib, obj))

    with open(COMPILE_COMMANDS_NAME, "w+", encoding="utf-8") as f:
        dump(commands, f, indent=4)


def make_cmds_single(config: DecompConfig, lib: Library, obj: Object) -> dict:
    """Creates clangd compilation commands for a single compilation unit

    Args:
        config (DecompConfig): Project configuration
        lib (Library): Parent library of the object
        obj (Object): Compilation unit

    Returns:
        dict: Clangd command objects
    """

    # Clangd arguments
    arguments = [
        "clang",
        "-fno-builtin",
        "-fno-short-enums",
        "-fno-cxx-exceptions",
        "-fno-rtti",
        "-fshort-wchar",
        "-Wno-invalid-offsetof",
        *lib.flags(),
    ]

    # Batch files define BATCH_* format macros for conditional compilation
    if type(obj) == Batch:
        arguments.append(f"-D{obj.macro_name()}")

    # Language standard flag
    if obj.is_cpp():
        arguments.append("-std=gnu++11")
    else:
        arguments.append("-std=gnu99")

    return {
        "directory": getcwd(),
        "file": abspath(obj.path()),
        "arguments": arguments,
    }


if __name__ == "__main__":
    main()
