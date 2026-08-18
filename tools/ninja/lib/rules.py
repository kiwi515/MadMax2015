# ============================================================================#
#                                                                             #
# Ninja build rule templates                                                  #
#                                                                             #
# ============================================================================#

from .config import DecompConfig
from .ninja_syntax import Writer


def rule_reconfigure(writer: Writer, config: DecompConfig):
    """Emits a Ninja build rule to re-run the configure script

    Args:
        writer (Writer): Ninja writer
        config (DecompConfig): Project configuration
    """

    writer.comment("Re-run generator script")
    writer.rule(
        name="reconfigure",
        command="$python $configure",
        description="CONFIGURE",
        generator=True,
    )
    writer.newline()


def rule_compile(writer: Writer, config: DecompConfig):
    """Emits a Ninja build rule to compile the specified source file

    Args:
        writer (Writer): Ninja writer
        config (DecompConfig): Project configuration
    """

    writer.comment("Compile source file")
    writer.rule(
        name="compile",
        command="$cc $cflags -MD -c $in -o $out",
        depfile="$depfile",
        deps="gcc",
        description="COMPILE $in",
    )
    writer.newline()
