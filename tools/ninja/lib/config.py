# ============================================================================#
#                                                                             #
# Project configuration                                                       #
#                                                                             #
# ============================================================================#

from dataclasses import dataclass, field
from os.path import abspath
from os.path import join as pathjoin
from os.path import normpath

import yaml

from .define import *


# ============================================================================#
# DecompConfig                                                               #
# ============================================================================#


@dataclass
class DecompConfig:
    """Represents the project configuration file.

    Data members are given values based on the `project.yaml` file.
    """

    PATH = "project.yaml"
    """Path to the project configuration file
    """

    @staticmethod
    def load() -> "DecompConfig":
        """Attempts to deserialize the config specified in the project config
        file

        Raises:
            Exception: Project config file is missing
        """

        try:
            with open(DecompConfig.PATH, "r", encoding="utf-8") as f:
                config_yaml = yaml.safe_load(f)

        except FileNotFoundError:
            raise Exception("Project config file is missing!")

        return DecompConfig(**config_yaml)

    # ========================================================================#
    # Misc. settings                                                          #
    # ========================================================================#

    docker_container: str = None
    """The name of the Docker container used to execute compile commands.
    """

    # ========================================================================#
    # Compiler settings                                                       #
    # ========================================================================#

    c_compiler: str = None
    """The name of the compiler executable that should be used for C code.
    It is assumed that this executable can be found using the $PATH variable.
    """

    cpp_compiler: str = None
    """The name of the compiler executable that should be used for C++ code.
    It is assumed that this executable can be found using the $PATH variable.
    """

    cflags_pedantic: list[str] = field(default_factory=list[str])
    """Compiler flags for enabling useful warnings.
    Only applied to decompiled code, not open-source libraries.
    """

    cflags_debug: list[str] = field(default_factory=list[str])
    """Compiler flags to apply across all module code in debug builds.
    """

    cflags_release: list[str] = field(default_factory=list[str])
    """Compiler flags to apply across all module code in release builds.
    """

    clangd_flags: list[str] = field(default_factory=list[str])
    """Additional flags to pass to the Clangd language parser.
    """

    # ========================================================================#
    # Directories                                                             #
    # ========================================================================#

    build_dir: str = "build"
    """The directory in which build artifacts are stored.
    """

    include_dir: str = "include"
    """The directory in which all C/C++ header files are stored.
    """

    src_dir: str = "src"
    """The directory in which all module source code is stored.
    """

    tools_dir: str = "tools"
    """The directory in which all build tools are stored.
    """

    src_extensions: list[str] = field(
        default_factory=lambda: [".c", ".cpp", ".cc", ".cxx", ".c++", ".inl", ".inc"])
    """All file extensions that signify C/C++ source code files.
    """

    def __post_init__(self):
        """Performs post-constructor initialization.

        This method is mostly reserved for class members that should not be
        configurable through the project YAML.
        """

        self.__normalize_paths()
        self.__find_tools()

    def __normalize_paths(self) -> None:
        """Normalizes all filepath members
        """

        self.build_dir = normpath(self.build_dir)
        self.include_dir = normpath(self.include_dir)
        self.src_dir = normpath(self.src_dir)
        self.tools_dir = normpath(self.tools_dir)

    def __find_tools(self) -> None:
        """Resolves filepaths to all tools needed by the project
        """

        # Configure script location
        self._configure: str = abspath(CONFIGURE_SCRIPT)

        # Clangd compiler command script location
        self._make_compile_cmds: str = abspath(pathjoin(
            self.tools_dir, MAKE_COMPILE_CMDS_SCRIPT))

        # Python executable location
        self._python = PYTHON

        # Ninja executable location
        self._ninja = NINJA
