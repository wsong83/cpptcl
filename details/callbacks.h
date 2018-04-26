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
class callback0 : public callback_base
{
     typedef R (*functor_type)();
     
public:
     callback0(functor_type f) : f_(f) {}
     
     virtual void invoke(Tcl_Interp *interp,
          int, Tcl_Obj * CONST [],
                         policies const &, ClientData)
     {
          dispatch<R>::do_dispatch(interp, f_);
     }

private:
     functor_type f_;
};

#define BOOST_PP_ITERATION_LIMITS (1, 9)
#define BOOST_PP_FILENAME_1       "preproc/callbacks.hpp"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_1
