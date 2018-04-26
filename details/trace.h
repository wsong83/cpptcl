// Copyright (c) 2011-2012, Wei Song
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

// this is not a stand alone header file

class trace_base {
public:
  virtual ~trace_base() {}
  
  virtual void invoke(Tcl_Interp *interp,
                      ClientData, const char *, const char *, int) = 0;
};

template <typename VT, typename CDT>
class trace : public trace_base {
  typedef VT (*functor_type) (VT const &, CDT *);
public:
  trace(functor_type f) : f_(f){}
  virtual ~trace() {}
  
  virtual void invoke(Tcl_Interp *interp, ClientData cData,
                      const char * VarName, const char *index, int flag) {
    // fetch the variable
    Tcl_Obj *var = Tcl_GetVar2Ex(interp, VarName, index, flag);
    VT orig = tcl_cast<VT>::from(interp, var);
    // run the trace
    VT rv = f_(orig, static_cast<CDT *>(cData));
    if(rv != orig) {
      // reset the variable
      var = tcl_cast<VT>::to(interp, rv);
      Tcl_Obj *prv = Tcl_SetVar2Ex(interp, VarName, index, var, flag);
      assert(prv == var);
    }
  }

private:
  functor_type f_;
};

// Local Variables:
// mode: c++
// End:
