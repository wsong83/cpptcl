// Copyright (c) 2011-2012, Wei Song
// Copyright (C) 2004-2006, Maciej Sobczak
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

// Note: this file is not supposed to be a stand-alone header

template <typename R>
class callback1<R, object const &> : public callback_base
{
     typedef object const & T1;
     typedef R (*functor_type)(T1);
     enum { var_start = 1 };
     
public:
     callback1(functor_type f) : f_(f) {}
     
     virtual void invoke(Tcl_Interp *interp,
          int objc, Tcl_Obj * CONST objv[],
                         policies const &pol, ClientData)
     {
          object t1 = get_var_params(interp, objc, objv, var_start, pol);
          dispatch<R>::template do_dispatch<T1>(interp, f_,
               t1);
     }

private:
     functor_type f_;
};

#define BOOST_PP_ITERATION_LIMITS (2, 9)
#define BOOST_PP_FILENAME_1       "preproc/callbacks_v.hpp"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_1
