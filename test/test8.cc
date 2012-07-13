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
 * Test case for variable trace
 * 08/07/2012   Wei Song
 *
 *
 */

#include "cpptcl.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using namespace Tcl;

interpreter i;

bool read_trace_bool(const bool& v, void *) {
  return !v;
}

bool write_trace_bool(const bool& v, void *) {
  return !v;
}

int read_trace_int(const int& v, int * cd) {
  *cd = v;
  return v+1;
}

int write_trace_int(const int& v, int * cd) {
  *cd = v;
  return v-1;
}

void test_read_trace() {
  //interpreter i;
  int env = 10;
  i.def_read_trace("vbool", "read_trace_bool", read_trace_bool); // add trace
  i.def_read_trace("vint", "read_trace_int", read_trace_int, &env);
  i.eval("set vbool 1"); // set variable
  string rv = i.eval("set vbool");   // read it
  assert(rv == "0");
  i.eval("set vint 17");
  string rv2 = i.eval("set vint");
  assert(rv2 == "18" && env == 17);
  i.undef_read_trace("vbool");                 // untrace with var name only
  i.undef_read_trace("vint", "read_trace_int"); // untrace with name
  i.eval("set vbool"); // error if not untraced
  i.eval("set vint");  // error if not untraced
}

void test_write_trace() {
  interpreter i;
  int env = 10;
  i.def_write_trace("vbool", "write_trace_bool", write_trace_bool); // add trace
  i.def_write_trace("vint", "write_trace_int", write_trace_int, &env);
  string rv = i.eval("set vbool 1"); // set variable
  assert(rv == "0");
  string rv2 = i.eval("set vint 17");
  assert(rv2 == "16" && env == 17);
  i.undef_write_trace("vbool");                 // untrace with var name only
  i.undef_write_trace("vint", "write_trace_int"); // untrace with name
  i.eval("set vbool 1"); // error if not untraced
  i.eval("set vint 19");  // error if not untraced
}

void test_read_and_write_trace() {
  //interpreter i;
  int env = 10;
  i.def_read_trace("vbool", "read_trace_bool", read_trace_bool); // add trace
  i.def_read_trace("vint", "read_trace_int", read_trace_int, &env);
  i.def_write_trace("vbool", "write_trace_bool", write_trace_bool); // add trace
  i.def_write_trace("vint", "write_trace_int", write_trace_int, &env);
  string rv = i.eval("set vbool 1"); // set variable
  assert(rv == "0");
  string rv1 = i.eval("set vbool");   // read it
  assert(rv1 == "1");
  string rv2 = i.eval("set vint 17");
  assert(rv2 == "16" && env == 17);
  string rv3 = i.eval("set vint");
  assert(rv3 == "17" && env == 16);
  i.undef_all_trace("vbool");      // untrace all
  i.undef_all_trace("vint");
  i.eval("set vbool 1"); // error if not untraced
  i.eval("set vbool"); // error if not untraced
  i.eval("set vint 17"); // error if not untraced
  i.eval("set vint");  // error if not untraced
}

int main() {
  try {
    test_read_trace();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << '\n';
  }

  try {
    test_write_trace();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << '\n';
  }

  try {
    test_read_and_write_trace();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << '\n';
  }

  return 0;
}
