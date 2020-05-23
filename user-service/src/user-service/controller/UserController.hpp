#ifndef example_user_UserController_hpp
#define example_user_UserController_hpp

#include "user-service/Constants.hpp"
#include "user-service/db/Database.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace user { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController) //<--- Codegen begin

class UserController : public oatpp::web::server::api::ApiController {
private:

  /**
   *  Inject Database component
   */
  OATPP_COMPONENT(std::shared_ptr<db::Database>, m_database, Qualifiers::SERVICE_USER);

public:

  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper, Qualifiers::SERVICE_USER) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

  ENDPOINT_INFO(createUser) {
    info->summary = "Create new User";
    info->addConsumes<Object<dto::UserDto>>("application/json");
    info->addResponse<Object<dto::UserDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/users", createUser,
           BODY_DTO(Object<dto::UserDto>, userDto)) {
    return createDtoResponse(Status::CODE_200, m_database->createUser(userDto));
  }


  ENDPOINT_INFO(putUser) {
    // general
    info->summary = "Update User by userId";
    info->addConsumes<Object<dto::UserDto>>("application/json");
    info->addResponse<Object<dto::UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("PUT", "/users/{userId}", putUser,
           PATH(Int64, userId),
           BODY_DTO(Object<dto::UserDto>, userDto)) {
    userDto->id = userId;
    return createDtoResponse(Status::CODE_200, m_database->updateUser(userDto));
  }


  ENDPOINT_INFO(getUserById) {
    // general
    info->summary = "Get one User by userId";
    info->addResponse<Object<dto::UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("GET", "/users/{userId}", getUserById,
           PATH(Int64, userId)) {
    auto user = m_database->getUserById(userId);
    OATPP_ASSERT_HTTP(user, Status::CODE_404, "User not found");
    return createDtoResponse(Status::CODE_200, user);
  }


  ENDPOINT_INFO(getUsers) {
    info->summary = "get all stored users";
    info->addResponse<List<Object<dto::UserDto>>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/users", getUsers) {
    return createDtoResponse(Status::CODE_200, m_database->getUsers());
  }


  ENDPOINT_INFO(deleteUser) {
    // general
    info->summary = "Delete User by userId";
    info->addResponse<String>(Status::CODE_200, "text/plain");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "/users/{userId}", deleteUser,
           PATH(Int64, userId)) {
    bool success = m_database->deleteUser(userId);
    OATPP_ASSERT_HTTP(success, Status::CODE_404, "User not deleted. Perhaps no such User in the Database");
    return createResponse(Status::CODE_200, "User successfully deleted");
  }

};

#include OATPP_CODEGEN_END(ApiController) //<--- Codegen end

}}}

#endif /* example_user_UserController_hpp */
