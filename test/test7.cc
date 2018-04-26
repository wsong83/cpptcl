// Copyright (c) 2011-2012, Wei Song
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

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

