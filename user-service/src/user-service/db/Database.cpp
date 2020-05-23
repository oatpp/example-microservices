
#include "Database.hpp"

namespace example { namespace user { namespace db {

model::User Database::serializeFromDto(const oatpp::Object<dto::UserDto> &userDto) {
  model::User user;
  if (userDto->id) {
    user.id = userDto->id;
  }
  user.name = userDto->name;
  return user;
}

oatpp::Object<dto::UserDto> Database::deserializeToDto(const model::User &user) {
  auto dto = dto::UserDto::createShared();
  dto->id = user.id;
  dto->name = user.name;
  return dto;
}

oatpp::Object<dto::UserDto> Database::createUser(const oatpp::Object<dto::UserDto> &userDto) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto user = serializeFromDto(userDto);
  user.id = m_idCounter++;
  m_usersById[user.id] = user;
  return deserializeToDto(user);
}

oatpp::Object<dto::UserDto> Database::updateUser(const oatpp::Object<dto::UserDto> &userDto) {
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

oatpp::Object<dto::UserDto> Database::getUserById(v_int64 id) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto it = m_usersById.find(id);
  if (it == m_usersById.end()) {
    return nullptr;
  }
  return deserializeToDto(it->second);
}

oatpp::List<oatpp::Object<dto::UserDto>> Database::getUsers() {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto result = oatpp::List<oatpp::Object<dto::UserDto>>::createShared();
  auto it = m_usersById.begin();
  while (it != m_usersById.end()) {
    result->push_back(deserializeToDto(it->second));
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
