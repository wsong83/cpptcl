#define n BOOST_PP_ITERATION()
     template <typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
     class_definer & def(std::string const &name,
          R (C::*f)(BOOST_PP_ENUM_PARAMS(n,T)), policies const &p = policies())
     {
          ch_->register_method(name,
               boost::shared_ptr<details::object_cmd_base>(
                    new details::BOOST_PP_CAT(method,n)<C, R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,T)>(f)),
               p);
          return *this;
     }

     template <typename R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)>
     class_definer & def(std::string const &name,
          R (C::*f)(BOOST_PP_ENUM_PARAMS(n,T)) const,
          policies const &p = policies())
     {
          ch_->register_method(name,
               boost::shared_ptr<details::object_cmd_base>(
                    new details::BOOST_PP_CAT(method,n)<C, R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,T)>(f)),
               p);
          return *this;
     }
#undef n
