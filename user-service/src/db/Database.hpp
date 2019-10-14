
#ifndef example_user_db_Database_hpp
#define example_user_db_Database_hpp

#include "../dto/UserDto.hpp"
#include "model/User.hpp"

#include "oatpp/core/concurrency/SpinLock.hpp"
#include <unordered_map>

namespace example { namespace user { namespace db {

/**
 *  Trivial in-memory Database based on unordered_map container.
 *  For demo purposes only :)
 */
class Database {
private:
  oatpp::concurrency::SpinLock m_lock;
  v_int64 m_idCounter; ///< counter to generate userIds
  std::unordered_map<v_int64, model::User> m_usersById; ///< Map userId to User
private:
  model::User serializeFromDto(const dto::UserDto::ObjectWrapper& userDto);
  dto::UserDto::ObjectWrapper deserializeToDto(const model::User& user);
public:
  
  Database()
    : m_idCounter(1)
  {

    /* Prepopulate Database */

    createUser(dto::UserDto::create(0, "F. Scott Fitzgerald"));
    createUser(dto::UserDto::create(0, "Harper Lee"));
    createUser(dto::UserDto::create(0, "J.K. Rowling"));
    createUser(dto::UserDto::create(0, "George Orwell"));
    createUser(dto::UserDto::create(0, "J.D. Salinger"));

  }
  
  dto::UserDto::ObjectWrapper createUser(const dto::UserDto::ObjectWrapper& userDto);
  dto::UserDto::ObjectWrapper updateUser(const dto::UserDto::ObjectWrapper& userDto);
  dto::UserDto::ObjectWrapper getUserById(v_int64 id);
  oatpp::data::mapping::type::List<dto::UserDto::ObjectWrapper>::ObjectWrapper getUsers();
  bool deleteUser(v_int64 id);
  
};

}}}

#endif /* example_user_db_Database_hpp */
