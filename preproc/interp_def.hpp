#define n BOOST_PP_ITERATION()
     template <typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
     void def(std::string const &name, R (*f)(BOOST_PP_ENUM_PARAMS(n,T)),
          policies const &p = policies())
     {
          add_function(name,
               boost::shared_ptr<details::callback_base>(
               new details::BOOST_PP_CAT(callback,n)<R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,T)>(f)), p);
     }
    
    // using the last arg as a client data, but must be pointer
    template <typename R, BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), typename T)>
    void def(std::string const &name, R (*f)(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1),T) *), BOOST_PP_CAT(T,n) *cData,
             policies const &p = policies()) {
      add_function(name,
                   boost::shared_ptr<details::callback_base>
                   (new details::BOOST_PP_CAT(BOOST_PP_CAT(callback,BOOST_PP_ADD(n,1)),_cd)<R, BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1),T)>(f)), p, (ClientData)(cData));
    }
#undef n
