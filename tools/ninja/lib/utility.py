# ============================================================================#
#                                                                             #
# Utility functions                                                           #
#                                                                             #
# ============================================================================#

from os import walk
from os.path import join as pathjoin
from os.path import sep, splitext


C_EXTENSIONS = (".c", ".c.inc")
CPP_EXTENSIONS = (".cc", ".cp", ".cpp", ".cxx", ".c++", ".inc", ".inl")


def find_files(root_path: str, extensions: list[str] = None) -> list[str]:
    """Searches recursively from the root path for all files matching any of
    the specified file extensions.

    If no extensions are specified, all files are allowed.

    Args:
        root_path (str): Root search path
        extensions (list[str]): File extensions

    Returns:
        list[str]: All files matching the specified conditions
    """

    found = []

    for dirpath, _, filenames in walk(root_path):

        for name in filenames:
            # Ignore hidden files
            if name.startswith("."):
                continue

            _, ext = splitext(name)

            if not extensions or ext in extensions:
                found.append(pathjoin(dirpath, name))

    # Alphabetical order
    found.sort()

    return found


def unix_path(path: str) -> str:
    """Converts a given filepath to UNIX format

    Args:
        path (str): Filepath

    Returns:
        str: UNIX filepath
    """

    return path.replace(sep, "/")
