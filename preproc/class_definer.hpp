// Copyright (c) 2011-2012, Wei Song
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

// this is not a stand alone header file

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
