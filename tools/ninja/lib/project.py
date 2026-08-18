# ============================================================================#
#                                                                             #
# Project interface                                                           #
#                                                                             #
# ============================================================================#

from io import StringIO
from os.path import exists as pathexists
from json import dump as jsondump

from .config import DecompConfig
from .define import COMPILE_COMMANDS_NAME
from .ninja_syntax import Writer
from .rules import rule_reconfigure, rule_compile
from .targets import target_compile, target_reconfigure
from .paths import Library


# ============================================================================#
# Configuration                                                               #
# ============================================================================#


NINJA_REQUIRED_VERSION = "1.3"
"""The minimum required version of Ninja to execute the resulting script
"""

NINJA_SCRIPT_NAME = "./build.ninja"
"""Name of the resulting Ninja build script
"""

OBJDIFF_CONFIG_NAME = "./objdiff.json"
"""Name of the objdiff configuration file
"""

# ============================================================================#
# DecompProject                                                              #
# ============================================================================#


class DecompProject:
    """Represents the build process.
    """

    def __init__(self, config: DecompConfig, libs: list[Library], is_ci: bool):
        """Constructor

        Args:
            config (DecompConfig): Project configuration
            libs (list[Library]): Libraries to include in the project
            is_ci (bool): Whether this script is running in a CI environment
        """

        self.config: DecompConfig = config
        self.libs: list[Library] = libs
        self.is_ci: bool = is_ci

    def emit_ninja(self) -> None:
        """Emits the Ninja build script (`build.ninja`)
        """

        output = StringIO()
        writer = Writer(output)

        self._emit_ninja_vars(writer)
        self._emit_ninja_rules(writer)
        self._emit_ninja_targets(writer)

        # Create ninja script
        with open(NINJA_SCRIPT_NAME, "w+", encoding="utf-8") as f:
            f.write(output.getvalue())

        writer.close()

    def emit_objdiff(self) -> None:
        """Emits the objdiff configuration file (`objdiff.json`)
        """

        json = {
            "min_version": "2.0.0-beta.5",
            "build_target": False,
            "watch_patterns": [
                "*.c", "*.cc", "*.cp", "*.cpp", "*.cxx", "*.c++",
                "*.h", "*.hh", "*.hp", "*.hpp", "*.hxx", "*.h++",
                "*.inc", "*.inl",
                "*.py", "*.yml", "*.txt", "*.json",
            ],
        }

        # CI will be running inside Linux already
        if self.is_ci:
            json["custom_make"] = self.config._ninja
            json["custom_args"] = []
        # Windows environments need to use Docker
        else:
            json["custom_make"] = "docker"
            json["custom_args"] = ["exec",
                                   self.config.docker_container,
                                   self.config._ninja]

        json["units"] = []

        for lib in self.libs:
            for obj in lib.objects():
                unit = {
                    "name": obj.name(),
                    "target_path": obj.target_object_path(),
                    "base_path": obj.base_object_path(),

                    "scratch": {
                        "platform": "windows",
                        "compiler": lib.config.cpp_compiler if obj.is_cpp else lib.config.c_compiler,
                        "c_flags": " ".join(lib.flags()),
                    },

                    "metadata": {
                        "reverse_fn_order": False,
                        "auto_generated": False,
                    }
                }

                # Additional settings when a source file is available
                if pathexists(obj.path()):
                    unit["scratch"].update({
                        "ctx_path": obj.context_path(),
                        "build_ctx": True,
                    })

                    unit["metadata"].update({
                        "complete": obj.is_matching(),
                        "source_path": obj.path(),
                    })

                json["units"].append(unit)

        # Create objdiff configuration file
        with open(OBJDIFF_CONFIG_NAME, "w+", encoding="utf-8") as f:
            jsondump(json, f, indent=4)

    def _emit_ninja_vars(self, writer: Writer) -> None:
        """Emits the variables section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (DecompConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Variables")
        writer.comment("==================================================")

        # Ninja requirements
        writer.comment("Ninja")
        writer.variable("ninja_required_version", NINJA_REQUIRED_VERSION)
        writer.newline()

        # Directories
        writer.comment("Directories")
        writer.variable("build_dir", self.config.build_dir)
        writer.variable("src_dir",   self.config.src_dir)
        writer.variable("tools_dir", self.config.tools_dir)
        writer.newline()

        # Tools
        writer.comment("Tools")
        writer.variable("cc",                self.config.c_compiler)
        writer.variable("cpp",               self.config.cpp_compiler)
        writer.variable("configure",         self.config._configure)
        writer.variable("make_compile_cmds", self.config._make_compile_cmds)
        writer.variable("python",            self.config._python)
        writer.newline()

        # Files
        writer.comment("Files")
        writer.variable("ninja_script",     NINJA_SCRIPT_NAME)
        writer.variable("compile_commands", COMPILE_COMMANDS_NAME)

    def _emit_ninja_rules(self, writer: Writer) -> None:
        """Emits the build rules section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (DecompConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Rules")
        writer.comment("==================================================")

        rule_reconfigure(writer, self.config)
        rule_compile(writer, self.config)

    def _emit_ninja_targets(self, writer: Writer) -> None:
        """Emits the build targets section of the Ninja build script

        Args:
            writer (Writer): Ninja writer
            config (DecompConfig): Project configuration
        """

        writer.comment("==================================================")
        writer.comment("Targets")
        writer.comment("==================================================")

        target_reconfigure(writer, self.config)

        for lib in self.libs:
            for obj in lib.objects():
                target_compile(writer, self.config, lib, obj)
