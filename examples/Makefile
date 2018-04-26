# Copyright (c) 2011-2012, Wei Song
#
# Permission to copy, use, modify, sell and distribute this software
# is granted provided this copyright notice appears in all copies.
# This software is provided "as is" without express or implied
# warranty, and with no claim as to its suitability for any purpose.
#

INCDIRS = -I. -I..

OUTPUTS = example1.so example3.so example4.so example5.so example7.so

all : ${OUTPUTS} example2 example6 

$(OUTPUTS) : %.so:%.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) $< ../cpptcl.o $(SHARED_LINKFLAGS) -o $@

example2 : example2.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) $< ../cpptcl.o $(OBJ_LINKFLAGS) -o $@

example6 : example6.cc ../cpptcl.o
	$(CXX) $(INCDIRS) $(CXXFLAGS) $< ../cpptcl.o $(OBJ_LINKFLAGS) -o $@

clean :
	-rm -f ${OUTPUTS} example2 example6
