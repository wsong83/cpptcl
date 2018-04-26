# Top level Makefile
# 04/07/2012   Wei Song
#
#

# global variables
# C++ compiler
export CXX = g++

# the Tcl library
OS_NAME := $(shell uname)
# Linux
ifeq ($(OS_NAME), Linux)
  TCL_OBJ_LINKFLAG = -ltcl
  TCL_SHARED_LINKFLAG = -shared
  PIC_FLAG = -fPIC
endif

# other systems, such as MinGW
ifneq ($(findstring MinGW, $(OS_NAME)),)
  TCL_OBJ_LINKFLAG = -ltcl85 -L/usr/local/lib
  TCL_SHARED_LINKFLAG = -shared $(shell which tcl85.dll)
  PIC_FLAG =
endif

# export the flags to all sub-directories
export CXXFLAGS = -std=c++0x -Wall -Wextra -g $(PIC_FLAG)
export OBJ_LINKFLAGS = $(TCL_OBJ_LINKFLAG)
export SHARED_LINKFLAGS = $(TCL_SHARED_LINKFLAG)

# local variables
INCDIRS = -I.
HEADERS = $(wildcard ./*.h)
HEADERS += $(wildcard ./details/*.h)
HEADERS += $(wildcard ./preproc/*.hpp)

# targets
TESTDIRS = test
EXAMPLEDIRS = examples

# actions

all: cpptcl.o

cpptcl.o : %.o:%.cc $(HEADERS)
	$(CXX) $(INCDIRS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean $(TESTDIRS) $(EXAMPLEDIRS)

test: cpptcl.o $(TESTDIRS)

example: cpptcl.o $(EXAMPLEDIRS)

$(TESTDIRS):
	$(MAKE) -C $@

$(EXAMPLEDIRS):
	$(MAKE) -C $@

clean:
	-rm *.o
	-for d in $(EXAMPLEDIRS); do $(MAKE) -C $$d clean; done
	-for d in $(TESTDIRS); do $(MAKE) -C $$d clean; done

