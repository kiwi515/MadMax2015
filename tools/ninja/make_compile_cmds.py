#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Clangd compile_commands.json generator                                      #
#                                                                             #
# ============================================================================#

from json import dump
from os import getcwd
from os.path import abspath, relpath
from os.path import join as pathjoin

from lib.config import DecompConfig
from lib.define import COMPILE_COMMANDS_NAME
from lib.paths import Object, Library, Batch
from lib.utility import find_files, C_EXTENSIONS, CPP_EXTENSIONS
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

    found = set()

    for lib in object_layout:
        # Emit commands for library objects
        for obj in lib.objects():
            commands.append(make_cmds_single(config, lib, obj))
            found.add(obj.path())

        # Search for files that may only be in a batch
        for it in find_files(
                pathjoin(config.src_dir, lib._prefix), C_EXTENSIONS + CPP_EXTENSIONS):

            # Prevent duplicates
            if it in found:
                continue

            # Convert to relative path
            it = relpath(it, config.src_dir)

            batch_obj = Object(obj.config, obj.is_matching(), it)
            commands.append(make_cmds_single(config, lib, batch_obj))
            found.add(it)

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

    # Fix include paths that are relative to the container
    arguments = [
        x.replace(f"/{config.docker_container}", "") for x in arguments]

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
