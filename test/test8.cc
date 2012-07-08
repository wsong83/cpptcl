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

bool read_trace_bool(const bool& v, void *) {
  cout << "read_trace_bool" << endl;
  return v;
}

bool write_trace_bool(const bool& v, void *) {
  cout << "write_trace_bool" << endl;
  return v;
}


void test_read_trace() {

  interpreter i;
  i.def_read_trace("vbool", read_trace_bool);
  i.def_read_trace("vbool", write_trace_bool);
  cout << (string)(i.eval("set vbool 1"));
  cout << (string)(i.eval("set vbool"));
  cout << (string)(i.eval("set another $vbool"));
}

void test_write_trace() {
}

void test_read_and_write_trace() {
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
