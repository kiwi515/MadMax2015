#!/usr/bin/env python3

# ============================================================================#
#                                                                             #
# Decomp project build script                                                 #
#                                                                             #
# ============================================================================#


import argparse

from tools.ninja.master_object_layout import create_object_layout
from tools.ninja.lib.project import DecompProject
from tools.ninja.lib.config import DecompConfig

parser = argparse.ArgumentParser()
parser.add_argument(
    "--ci",
    action="store_true",
    help="generate commands for a CI environment (no docker)"
)
args = parser.parse_args()

# Create list of libraries and objects
config = DecompConfig.load()
object_layout = create_object_layout(config)

# Write build.ninja and objdiff.json
project = DecompProject(config, object_layout, args.ci)
project.emit_ninja()
project.emit_objdiff()
