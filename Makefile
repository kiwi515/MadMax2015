# Producer Target String:
# GNU C++ 4.8.1 -msse2 -mcx16 -mtune=generic -march=x86-64 -g -O3 -std=gnu++11 -fno-common -fPIC -fvisibility=hidden -fstack-protector

export MSYS2_ARG_CONV_EXCL=*

.SUFFIXES:

CC  := /opt/gcc-4.8.1/bin/gcc
CXX := /opt/gcc-4.8.1/bin/g++

MM_PROJECT_DIR := /decomp/objdiff_project/src/Volumes/bobsource/madmax/companies/feral/development/products/madmax/source/perforce/mm/branch/world/source
MM_CTG_DIR := /decomp/objdiff_project/src/Volumes/bobsource/madmax/companies/feral/development/products/madmax/source/perforce/ctg

# Default Flags
CFLAGS   := -msse2 -mcx16 -mtune=generic -march=x86-64 -g -O3 -std=gnu99 -fno-common -fPIC -fvisibility=hidden -fstack-protector -DNDEBUG -I$(MM_PROJECT_DIR) -I$(MM_CTG_DIR)
CXXFLAGS := -msse2 -mcx16 -mtune=generic -march=x86-64 -g -O3 -std=gnu++11 -fno-common -fPIC -fvisibility=hidden -fvisibility-inlines-hidden -fstack-protector -DNDEBUG -I$(MM_PROJECT_DIR) -I$(MM_CTG_DIR)


###
#	Library make file adjustments
###

STUNTMAN_DIR := src/Volumes/BobSource/madmax/Companies/Feral/Development/Libraries/StuntMan/StuntMan-1.2.8/Source

# Auto-include every directory under StuntMan Source
STUNTMAN_INCLUDES := $(addprefix -I,$(shell find $(STUNTMAN_DIR) -type d 2>/dev/null))

# Target-specific CXXFLAGS for StuntMan object files
base_objects/Volumes/BobSource/madmax/Companies/Feral/Development/Libraries/StuntMan/%.cpp.o: \
	CXXFLAGS := -msse2 -mcx16 -mtune=generic -march=x86-64 -g -O3 -std=gnu++11 -fPIC -fvisibility=hidden -fstack-protector -DNDEBUG $(STUNTMAN_INCLUDES)

MINIUPNP_DIR := src/Volumes/BobSource/madmax/Companies/Feral/Development/Libraries/MiniUPnP/MiniUPnPc-1.9/Source
MINIUPNP_INCLUDES := $(addprefix -I,$(shell find $(MINIUPNP_DIR) -type d 2>/dev/null))

# Target-specific CFLAGS for MiniUPnP object files (.c)
base_objects/Volumes/BobSource/madmax/Companies/Feral/Development/Libraries/MiniUPnP/%.c.o: \
    CFLAGS := -msse2 -mcx16 -mtune=generic -march=x86-64 -g -O3 -fPIC -fvisibility=hidden -fstack-protector $(MINIUPNP_INCLUDES)


###
#	make file arguments
###

base_objects/%.cxx.o: src/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

base_objects/%.cpp.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

base_objects/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf base_objects