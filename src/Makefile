PROJECT_NAME = PACKS

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=gbc
# CFLAGS = --std-c23

# Builds all targets sequentially
all: $(TARGETS)

# Number of banks (must be a power of 2): A (Automatic), 2, 4, 8, 16, 32...
N_BANKS = A

# Default hardware sprites size: SPRITES_8x16(default) or SPRITES_8x8
DEFAULT_SPRITES_SIZE = SPRITES_8x8

include $(subst ',,$(subst \,/,'$(ZGB_PATH)'))/src/MakefileCommon
