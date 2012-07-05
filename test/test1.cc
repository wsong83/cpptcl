/*
 * Copyright (c) 2011-2012 Wei Song <songw@cs.man.ac.uk> 
 *    Advanced Processor Technologies Group, School of Computer Science
 *    University of Manchester, Manchester M13 9PL UK
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/* 
 * Add extra argument to support client data
 * 05/07/2012   Wei Song
 *
 *
 */
//
// Copyright (C) 2004-2006, Maciej Sobczak
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#include "cpptcl.h"
#include <iostream>

using namespace Tcl;

static int data = 0;
static interpreter gi;

void fun0() {}
int fun1() { return 8; }
int fun2(int i) { return i + 2; }
int fun3(int const &i) { return i + 2; }
int fun4(std::string const &s) { return s.size(); }
int fun5(char const *s) { return std::string(s).size(); }

// functions use client data
int fund1(int * d) { return ++(*d);}
int fund2(int d0, int* d) { *d += d0; return *d;}
int fund3(int d0, int d1, int* d) { *d += d0 + d1; return *d;}
int fund4(int d0, int d1, int d2, 
          int* d) { *d += d0 + d1 + d2; return *d;}
int fund5(int d0, int d1, int d2, 
          int d3, int* d) { 
  *d += d0 + d1 + d2 + d3; return *d;
}
int fund6(int d0, int d1, int d2, 
          int d3, int d4, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4; return *d;
}
int fund7(int d0, int d1, int d2, 
          int d3, int d4, int d5, 
          int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5; 
  return *d;
}
int fund8(int d0, int d1, int d2, 
          int d3, int d4, int d5, 
          int d6, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5 + d6; 
  return *d;
}
int fund9(int d0, int d1, int d2, 
          int d3, int d4, int d5, 
          int d6, int d7, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7; 
  return *d;
}

// client data with object
int funod2(const object& d0, int* d) { *d += d0.get<int>(gi); return *d;}
int funod3(int d0, const object& d1, int* d) { *d += d0 + d1.get<int>(gi); return *d;}
int funod4(int d0, int d1, const object& d2, 
          int* d) { *d += d0 + d1 + d2.get<int>(gi); return *d;}
int funod5(int d0, int d1, int d2, 
          const object& d3, int* d) { 
  *d += d0 + d1 + d2 + d3.get<int>(gi); return *d;
}
int funod6(int d0, int d1, int d2, 
          int d3, const object& d4, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4.get<int>(gi); return *d;
}
int funod7(int d0, int d1, int d2, 
          int d3, int d4, const object& d5, 
          int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5.get<int>(gi); 
  return *d;
}
int funod8(int d0, int d1, int d2, 
          int d3, int d4, int d5, 
          const object& d6, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5 + d6.get<int>(gi); 
  return *d;
}
int funod9(int d0, int d1, int d2, 
          int d3, int d4, int d5, 
          int d6, const object& d7, int* d) { 
  *d += d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7.get<int>(gi); 
  return *d;
}


void test1()
{
     interpreter i;
     i.make_safe();
     
     std::string s = i.eval("return \"ala ma kota\"");
     assert(s == "ala ma kota");

     i.eval("proc myproc {} { return 7 }");
     s = static_cast<std::string>(i.eval("myproc"));
     assert(s == "7");
     
     int ival = i.eval("myproc");
     assert(ival == 7);
     double dval = i.eval("myproc");
     assert(dval == 7.0);
     
     i.def("fun0", fun0);
     i.eval("fun0");
     
     i.def("fun1", fun1);
     ival = i.eval("fun1");
     assert(ival == 8);
     
     i.def("fun2", fun2);
     ival = i.eval("fun2 7");
     assert(ival == 9);
     
     i.def("fun3", fun3);
     ival = i.eval("fun3 7");
     assert(ival == 9);
     
     i.def("fun4", fun4);
     ival = i.eval("fun4 \"ala ma kota\"");
     assert(ival == 11);

     i.def("fun5", fun5);
     ival = i.eval("fun5 \"ala ma kotka\"");
     assert(ival == 12);
     
     try
     {
          i.eval("fun2 notaninteger");
          assert(false);
     }
     catch (std::exception const &) {}

     // test for client data
     i.def("fund1", fund1, &data);
     i.def("fund2", fund2, &data);
     i.def("fund3", fund3, &data);
     i.def("fund4", fund4, &data);
     i.def("fund5", fund5, &data);
     i.def("fund6", fund6, &data);
     i.def("fund7", fund7, &data);
     i.def("fund8", fund8, &data);
     i.def("fund9", fund9, &data);
     i.def("funod2", funod2, &data);
     i.def("funod3", funod3, &data);
     i.def("funod4", funod4, &data);
     i.def("funod5", funod5, &data);
     i.def("funod6", funod6, &data);
     i.def("funod7", funod7, &data);
     i.def("funod8", funod8, &data);
     i.def("funod9", funod9, &data);

     int rv;
     rv = i.eval("fund1");
     assert(rv == 1);
     rv = i.eval("fund2 1");
     assert(rv == 2);
     rv = i.eval("fund3 1 1");
     assert(rv == 4);
     rv = i.eval("fund4 1 1 1");
     assert(rv == 7);
     rv = i.eval("fund5 1 1 1 1");
     assert(rv == 11);
     rv = i.eval("fund6 1 1 1 1 1");
     assert(rv == 16);
     rv = i.eval("fund7 1 1 1 1 1 1");
     assert(rv == 22);
     rv = i.eval("fund8 1 1 1 1 1 1 1");
     assert(rv == 29);
     rv = i.eval("fund9 1 1 1 1 1 1 1 1");
     assert(rv == 37);
     rv = i.eval("funod2 1");
     assert(rv == 38);
     rv = i.eval("funod3 1 1");
     assert(rv == 40);
     rv = i.eval("funod4 1 1 1");
     assert(rv == 43);
     rv = i.eval("funod5 1 1 1 1");
     assert(rv == 47);
     rv = i.eval("funod6 1 1 1 1 1");
     assert(rv == 52);
     rv = i.eval("funod7 1 1 1 1 1 1");
     assert(rv == 58);
     rv = i.eval("funod8 1 1 1 1 1 1 1");
     assert(rv == 65);
     rv = i.eval("funod9 1 1 1 1 1 1 1 1");
     assert(rv == 73);
     
}

int main()
{
     try
     {
          test1();
     }
     catch (std::exception const &e)
     {
          std::cerr << "Error: " << e.what() << '\n';
     }
}
