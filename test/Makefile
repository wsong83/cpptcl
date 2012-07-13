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
# Makefile
# 04/07/2012   Wei Song
#
#

INCDIRS = -I. -I..

OUTPUTS = test1 test3 test4 test5 test6 test7 test8

all : build test2.so test9 dotest

build : $(OUTPUTS)

$(OUTPUTS) : %:%.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) $< ../cpptcl.o $(OBJ_LINKFLAGS) -o $@

test2.so : test2.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) $< ../cpptcl.o $(SHARED_LINKFLAGS) -o $@

test9: test8.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) -c test8.cc -o test8.o
	$(CXX) ../cpptcl.o test8.o $(OBJ_LINKFLAGS) -o $@

dotest :
	./test1
	tclsh test2.tcl
	./test3
	./test4
	./test5
	./test6
	./test7
	./test8
	./test9

clean :
	-rm -f ${OUTPUTS} test2.so test8.o test9
