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

#include "cpptcl.h"

static int gdata = 2;        // a global data

void fun(int d, int * gd) {  // gd comes from environment
  *gd += d;
}

int main() {
  Tcl::interpreter i;
  
  i.def("fun", fun, &gdata); // send gdata to the Tcl fun
  
  i.eval("fun 10");          // only one argument is passed by Tcl command
  assert(gdata == 12);       // check the global data is changed

  return 0;
}

