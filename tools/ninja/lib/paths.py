# ============================================================================#
#                                                                             #
# Filepath wrappers                                                           #
#                                                                             #
# ============================================================================#

from os.path import join as pathjoin
from os.path import split, splitext, basename
from typing import Optional

from .config import DecompConfig

# ============================================================================#
# PathObj                                                                     #
# ============================================================================#


class PathObj:
    """Represents a file in the project.
    """

    def __init__(self, config: DecompConfig, path: str):
        """Constructor

        Args:
            config (DecompConfig): Project configuration
            path (str): File path
        """

        self.config = config
        self._path = path

    def path(self) -> str:
        """Gets the path to this file
        """

        return self._path

    def name(self) -> str:
        """Gets the name/basepath of this file
        """

        return splitext(self._path)[0]

    def directory(self) -> str:
        """Gets the path to the directory containing this file
        """

        return split(self._path)[0]

    def extension(self) -> str:
        """Gets the extension of this file
        """

        return splitext(self._path)[-1]

    def with_extension(self, extension: str) -> str:
        """Applies the specified file extension to this file path.
        `Ex: "source.cpp" -> "source.cpp.o"`

        Args:
            extension (str): File extension
        """

        return f"{self._path}{extension}"


# ============================================================================#
# Object                                                                      #
# ============================================================================#


class Object(PathObj):
    """Represents a translation/compilation unit in the project.
    """

    def __init__(self, config: DecompConfig, is_matching: bool, src_path: str):
        """Constructor

        Args:
            config (DecompConfig): Project configuration
            is_matching (bool): Whether the file is fully matching
            src_path (str): Source file path
        """

        super().__init__(config, src_path)
        self._is_matching = is_matching

    def is_matching(self) -> bool:
        """Tests whether this object file is fully matching
        """
        return self._is_matching

    def is_cpp(self) -> bool:
        """Tests whether this object was generated from a C++ source file.
        """

        return self.extension() in (
            ".cc", ".cp", ".cpp", ".cxx", ".c++", ".inl"
        )

    def path(self) -> str:
        """Gets the path to this file
        """

        return pathjoin(
            self.config.src_dir,
            self._path)

    def base_object_path(self) -> str:
        """Gets the path to the base (compiled) object file for this translation unit
        """

        return pathjoin(
            self.config.build_dir,
            "src",
            self.with_extension(".o"))

    def target_object_path(self) -> str:
        """Gets the path to the target (split) object file for this translation unit
        """

        return pathjoin(
            self.config.build_dir,
            "obj",
            self.with_extension(".o"))

    def dependency_path(self) -> str:
        """Gets the path to the dependency file generated for this translation
        unit
        """

        return pathjoin(
            self.config.build_dir,
            self.with_extension(".d"))

    def context_path(self) -> str:
        """Gets the path to the decomp.me context file generated for this
        translation unit
        """

        return pathjoin(
            self.config.build_dir,
            "src",
            self.with_extension(".ctx"))


# ============================================================================#
# Batch                                                                       #
# ============================================================================#


class Batch(Object):
    """Represents an aggregated set of objects in the project.
    """

    def __init__(self, config: DecompConfig, is_matching: bool, src_path: str):
        """Constructor

        Args:
            config (DecompConfig): Project configuration
            is_matching (bool): Whether the file is fully matching
            src_path (str): Source file path
        """

        super().__init__(config, is_matching, src_path)

    def macro_name(self) -> str:
        """Gets the name of the preprocessor BATCH_* macro that should be used
        when compiling this batch file
        """

        return basename(self.name()).upper()


# ============================================================================#
# Library                                                                     #
# ============================================================================#


class Library:
    """Represents a collection of translation/compilation units in the project.
    """

    def __init__(self, config: DecompConfig, *, name: str, prefix: str,
                 flags: list[str], objects: list[Object]):
        """Constructor

        Args:
            config (DecompConfig): Project configuration
            name (str): Library name
            prefix (str): Common directory prefix
            flags (list[str]): Compiler flags
            objects (list[Object]): Translation/compilation units
        """

        self.config = config
        self._name = name
        self._prefix = prefix
        self._flags = flags
        self._objects = objects

        # Apply library prefix path, so we can shorten source file paths
        if prefix:
            for obj in self._objects:
                obj._path = f"{prefix}{obj._path}"

    def name(self) -> str:
        """Gets the name of this library
        """

        return self._name

    def flags(self) -> str:
        """Gets the compiler flags used by this library 
        """

        return self._flags

    def objects(self) -> list[Object]:
        """Gets the translation/compilation units included in this library
        """

        return self._objects

    def find_object(self, name: str) -> Object:
        """Attempts to find an object by its unique name
        """

        return self._objects_dict[name]
