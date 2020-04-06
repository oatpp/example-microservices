
#include "Database.hpp"

namespace example { namespace user { namespace db {

model::User Database::serializeFromDto(const dto::UserDto::ObjectWrapper &userDto) {
  model::User user;
  if (userDto->id) {
    user.id = userDto->id->getValue();
  }
  user.name = userDto->name;
  return user;
}

dto::UserDto::ObjectWrapper Database::deserializeToDto(const model::User &user) {
  auto dto = dto::UserDto::createShared();
  dto->id = user.id;
  dto->name = user.name;
  return dto;
}

dto::UserDto::ObjectWrapper Database::createUser(const dto::UserDto::ObjectWrapper &userDto) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto user = serializeFromDto(userDto);
  user.id = m_idCounter++;
  m_usersById[user.id] = user;
  return deserializeToDto(user);
}

dto::UserDto::ObjectWrapper Database::updateUser(const dto::UserDto::ObjectWrapper &userDto) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto user = serializeFromDto(userDto);
  if (user.id < 0) {
    throw std::runtime_error("User Id cannot be less than 0");
  }
  auto it = m_usersById.find(user.id);
  if (it != m_usersById.end()) {
    m_usersById[user.id] = user;
  } else {
    throw new std::runtime_error("Such user not found");
  }
  return deserializeToDto(user);
}

dto::UserDto::ObjectWrapper Database::getUserById(v_int64 id) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto it = m_usersById.find(id);
  if (it == m_usersById.end()) {
    return nullptr;
  }
  return deserializeToDto(it->second);
}

oatpp::data::mapping::type::List<dto::UserDto::ObjectWrapper>::ObjectWrapper Database::getUsers() {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto result = oatpp::data::mapping::type::List<dto::UserDto::ObjectWrapper>::createShared();
  auto it = m_usersById.begin();
  while (it != m_usersById.end()) {
    result->pushBack(deserializeToDto(it->second));
    it++;
  }
  return result;
}

bool Database::deleteUser(v_int64 id) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto it = m_usersById.find(id);
  if (it == m_usersById.end()) {
    return false;
  }
  m_usersById.erase(it);
  return true;
}

}}}
