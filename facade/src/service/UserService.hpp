#ifndef example_facade_example_userService
#define example_facade_example_userService

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace service {

#include OATPP_CODEGEN_BEGIN(ApiClient)

class UserService : public oatpp::web::client::ApiClient {
public:

  API_CLIENT_INIT(UserService)

  API_CALL("GET", "/users", getUsers)
  API_CALL("GET", "/users/{userId}", getUserById, PATH(Int64, userId))

};

#include OATPP_CODEGEN_END(ApiClient)

}}}

#endif //example_facade_example_userService