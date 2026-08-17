# ============================================================================#
#                                                                             #
# Shared constants                                                            #
#                                                                             #
# ============================================================================#

import sys
from os.path import join as pathjoin

PYTHON = sys.executable
"""Path to the Python executable used to invoke this script
"""

NINJA = "ninja"
"""Path to the Ninja executable
"""

CONFIGURE_SCRIPT = "./configure.py"
"""Name of the main configure script
"""

MAKE_COMPILE_CMDS_SCRIPT = pathjoin("ninja", "make_compile_cmds.py")
"""Tools directory path to the Clangd compile commands script
"""

COMPILE_COMMANDS_NAME = "./compile_commands.json"
"""Name of the Clangd compile commands file
"""
