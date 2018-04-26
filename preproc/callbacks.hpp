// Copyright (c) 2011-2012, Wei Song
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

// this is not a stand alone header file

#define n BOOST_PP_ITERATION()

#define dispatch_print(z, n, data) \
tcl_cast<BOOST_PP_CAT(T,n)>::from(interp, objv[BOOST_PP_INC(n)])

template <typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
class BOOST_PP_CAT(callback,n) : public callback_base
{
     typedef R (*functor_type)(BOOST_PP_ENUM_PARAMS(n,T));
     
public:
     BOOST_PP_CAT(callback,n)(functor_type f) : f_(f) {}
     
     virtual void invoke(Tcl_Interp *interp,
          int objc, Tcl_Obj * CONST objv[],
          policies const &, ClientData)
     {
          check_params_no(objc, BOOST_PP_INC(n));
          
          dispatch<R>::template do_dispatch<BOOST_PP_ENUM_PARAMS(n,T)>(interp, f_,
               BOOST_PP_ENUM(n, dispatch_print, ~));
     }

private:
     functor_type f_;
};

#undef dispatch_print
#undef n
