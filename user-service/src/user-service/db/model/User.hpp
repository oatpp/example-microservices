

#ifndef example_user_db_model_User_hpp
#define example_user_db_model_User_hpp

#include "oatpp/core/Types.hpp"

#include <string>
#include <list>

namespace example { namespace user { namespace db { namespace model {

/**
 *  Object of User stored in the Demo-Database
 */
class User {
public:
  v_int64 id;
  oatpp::String name;
};

}}}}

#endif /* example_user_db_model_User_hpp */
