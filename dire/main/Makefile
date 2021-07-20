# Makefile is a part of the DIRE parton shower.
# Copyright (C) 2016 Stefan Prestel.
# Author: Stefan Prestel (heavily relying on the PYTHIA examples Makefile
# by Philip Ilten)
#
# Example usage is:
#     make dire00

################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Include the PYTHIA (!) and DIRE configuration files (note that Dire conf. is
# included first, to get the paths to Pythia, and then again, to overwrite
# dangerous Pythia variables)
PYTHIA_LIB_SUFFIX=.a
CXX_ADDITIONAL=
-include Makefile.inc
ifneq ("$(wildcard $(PYTHIA8_PREFIX)/Makefile.inc)","")
-include $(PYTHIA8_PREFIX)/Makefile.inc
ifeq ($(ENABLE_SHARED),true)
  PYTHIA_LIB_SUFFIX=$(LIB_SUFFIX)
  CXX_ADDITIONAL+=-L$(PYTHIA8_PREFIX)/lib -Wl,-rpath $(PYTHIA8_PREFIX)/lib -lpythia8
  ifeq ($(LHAPDF6_USE),true)
    PYTHIA_LIB_SUFFIX=lhapdf6.so
  endif
endif
-include Makefile.inc
else
-include $(PYTHIA8_PREFIX)/share/Pythia8/examples/Makefile.inc
ifeq ($(ENABLE_SHARED),true)
  PYTHIA_LIB_SUFFIX=$(LIB_SUFFIX)
  CXX_ADDITIONAL+=-L$(PYTHIA8_PREFIX)/lib -Wl,-rpath $(PYTHIA8_PREFIX)/lib -lpythia8
  ifeq ($(LHAPDF6_USE),true)
    PYTHIA_LIB_SUFFIX=lhapdf6.so
  endif
endif
-include Makefile.inc
endif

# Handle GZIP support.
GZIP_COMMON=
ifeq ($(GZIP_USE),true)
  GZIP_COMMON+= -DGZIPSUPPORT -I$(GZIP_INCLUDE)
  GZIP_COMMON+= -L$(GZIP_LIB) -Wl,-rpath $(GZIP_LIB) -lz
endif

# Handle OPENMP support.
ifeq ($(OPENMP_USE),true)
  CXX_COMMON+= -fopenmp -DOPENMP
endif

CXX_COMMON:=-I$(PYTHIA8_INCLUDE) $(CXX_COMMON) -pedantic -W -Wall -Wshadow -fPIC -Wl,-rpath $(PYTHIA8_LIB) -ldl
CXX_COMMON:=$(shell echo $(CXX_COMMON) | sed 's|-O1||g' | sed 's|-O2||g' | sed 's|-O3||g')
CXX_COMMON:=$(shell echo $(CXX_COMMON) | sed 's|-std=c++98||g')
#CXX_COMMON+= -std=c++14 -O2
#CXX_COMMON+= -std=c++11 -O2 -g
CXX_COMMON+= -std=c++11 -O0 -g
#CXX_COMMON+= -std=c++14 -g -fsanitize=leak -fsanitize=address -fno-omit-frame-pointer

APFEL_INC=$(PREFIX_INCLUDE)/../../apfelxx/build/include
APFEL_LIB=$(PREFIX_INCLUDE)/../../apfelxx/build/lib
APFEL_BIN=$(PREFIX_INCLUDE)/../../apfelxx/build/bin

DIRE_INCLUDE=$(PREFIX_INCLUDE)
DIRE_SRC=$(PREFIX_SRC)
DIRE_LIB=$(PREFIX_LIB)
DIRE_CONFIG_BIN=$(PREFIX_BIN)/dire-config
DIRE_CONFIG=`$(DIRE_CONFIG_BIN) --all-libs`
DIRE_CONFIG_NOOPEMMP=$(shell $(DIRE_CONFIG_BIN) --all-libs | sed 's,-fopenmp,,g' | sed "s,-DOPENMP,,g")

DIRE_LIB_SUFFIX=.a
ifeq ($(ENABLE_SHARED),true)
  DIRE_LIB_SUFFIX=$(LIB_SUFFIX)
  CXX_ADDITIONAL+=-L$(DIRE_LIB) -Wl,-rpath $(DIRE_LIB) -ldire
endif

MODEL=$(MG5MES_MODEL)
ifeq ($(MG5MES_USE),true)
  CXX_COMMON+= -DMG5MES
  CXX_COMMON+= -include $(MG5MES_INCLUDE)/Processes_$(MODEL)/Parameters_$(MODEL).h
  CXX_COMMON+= -include $(MG5MES_INCLUDE)/Processes_$(MODEL)/PY8ME.h
  CXX_COMMON+= -include $(MG5MES_INCLUDE)/Processes_$(MODEL)/PY8MEs.h
endif

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# PYTHIA libraries.
$(PYTHIA8_LIB)/libpythia8$(PYTHIA_LIB_SUFFIX):
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory $(PYTHIA8_LIB))

# Try to make DIRE libraries again, if necessary.
$(DIRE_LIB)/libdire$(DIRE_LIB_SUFFIX): $(DIRE_SRC)/*.cc \
	$(wildcard $(DIRE_INCLUDE)/*/*.h)
ifeq ("$(wildcard $(PWD)/../Makefile)","") 
	@echo "Dire source has been changed. Please recompile source."
else
	@echo "Dire source has been changed. Recompiling in source directory."
	cd ..; $(MAKE); cd main
endif

# Examples without external dependencies.
dire : $$@.cc
	@echo "Default compilation with ''$(CXX) $^ -o $@ $(DIRE_CONFIG)''"
	$(CXX) $^ -o $@ $(DIRE_CONFIG) -I$(APFEL_INC) -L$(APFEL_LIB) -Wl,-rpath,$(APFEL_LIB) -lapfelxx
dire-new : $$@.cc
	@echo "Default compilation with ''$(CXX) $^ -o $@ $(DIRE_CONFIG)''"
	$(CXX) $^ -o $@ $(DIRE_CONFIG)
#dire% : $$@.cc
#	@echo "Default compilation with ''$(CXX) $^ -o $@ $(DIRE_CONFIG)'' -L$(APFEL_LIB) -Wl,-rpath,$(APFEL_LIB) -lapfelxx"
#	$(CXX) $^ -o $@ $(DIRE_CONFIG) -L$(APFEL_LIB) -Wl,-rpath,$(APFEL_LIB) -lapfelxx
dire% : $$@.cc
	@echo "Default compilation with ''$(CXX) $^ -o $@ $(DIRE_CONFIG)''"
	$(CXX) $^ -o $@ $(DIRE_CONFIG)

# Make DIRE main programs with HepMC dependence.
dire01 dire02 dire03 dire022: $$@.cc $(DIRE_LIB)/libdire$(DIRE_LIB_SUFFIX)\
	$(PYTHIA8_LIB)/libpythia8$(PYTHIA_LIB_SUFFIX)
ifeq ($(HEPMC2_USE),true)
	$(CXX) $^ -o $@ -I$(DIRE_INCLUDE) -I$(HEPMC2_INCLUDE) $(CXX_COMMON)\
	 $(CXX_ADDITIONAL) -L$(HEPMC2_LIB) -Wl,-rpath $(HEPMC2_LIB) -lHepMC $(GZIP_COMMON)
else
	@echo "Error: $@ requires HEPMC2"
endif

# PROMC.
dire04: $$@.cc $(DIRE_LIB)/libdire$(DIRE_LIB_SUFFIX) $(PYTHIA8_LIB)/libpythia8$(PYTHIA_LIB_SUFFIX)
ifeq ($(PROMC_USE),true)
	$(CXX) $^ -o $@ -I$(DIRE_INCLUDE) -I$(PROMC_INCLUDE)/src -I$(PROMC_INCLUDE)/include\
	 $(CXX_COMMON) $(CXX_ADDITIONAL) -DPROMC=\"$(PROMC_INCLUDE)\" -Wno-long-long\
	 -L$(PROMC_LIB) -Wl,-rpath,$(PROMC_LIB) -lpromc -lprotoc -lprotobuf\
	 -lprotobuf-lite -lcbook $(GZIP_COMMON)
else
	@echo "Error: $@ requires PROMC"
endif

# Make DIRE main program with JavaScript dependence.
dire-viz: $$@.cc $(DIRE_LIB)/libdire$(DIRE_LIB_SUFFIX)\
	$(PYTHIA8_LIB)/libpythia8$(PYTHIA_LIB_SUFFIX)
	@echo "Copying template html file"
	cp $(DIRE_INCLUDE)/DirePlugins/visualization/template.html .
	@echo "Copying javascript and json files"
	cp $(DIRE_INCLUDE)/DirePlugins/visualization/*.js .
	cp $(DIRE_INCLUDE)/DirePlugins/visualization/*.json .
	@echo "Compilation with ''$(CXX) $^ -o $@ $(DIRE_CONFIG)''"
	$(CXX) $^ -o $@ $(DIRE_CONFIG)

# Clean.
clean:
	@rm -f dire;\
	 rm -f dire[0-9][0-9];\
	 rm -f dire-viz template.html OrbitControls.js dat.gui.min.js three.min.js helvetiker_regular.typeface.json
