# Copyright (c) 2011-2012 Wei Song <songw@cs.man.ac.uk> 
#    Advanced Processor Technologies Group, School of Computer Science
#    University of Manchester, Manchester M13 9PL UK
#
#    This source code is free software; you can redistribute it
#    and/or modify it in source code form under the terms of the GNU
#    General Public License as published by the Free Software
#    Foundation; either version 2 of the License, or (at your option)
#    any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
#
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
endif

# other systems, such as MinGW
ifeq ($(OS_NAME), MinGW)
  TCL_OBJ_LINKFLAG = -ltcl
  TCL_SHARED_LINKFLAG = -shared $(shell which tcl85.dll)
endif

# export the flags to all sub-directories
export CXXFLAGS = -std=c++0x -Wall -Wextra -g -fPIC
export OBJ_LINKFLAGS = $(TCL_OBJ_LINKFLAG)
export SHARED_LINKFLAGS = $(TCL_SHARED_LINKFLAG)

# local variables
INCDIRS = -I./
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
	-rm bin/avs_shell

