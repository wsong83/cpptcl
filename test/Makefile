# Copyright (c) 2011-2012, Wei Song
#
# Permission to copy, use, modify, sell and distribute this software
# is granted provided this copyright notice appears in all copies.
# This software is provided "as is" without express or implied
# warranty, and with no claim as to its suitability for any purpose.
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
