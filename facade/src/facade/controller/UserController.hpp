#ifndef example_facade_UserController_hpp
#define example_facade_UserController_hpp

#include "facade/Constants.hpp"

#include "facade/dto/UserDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/data/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController) //<--- codegen begin

class UserController : public oatpp::web::server::api::ApiController {
public:

  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper, Qualifiers::SERVICE_FACADE) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

  // TODO - endpoints here

};

#include OATPP_CODEGEN_END(ApiController) //<--- codegen end

}}}

#endif /* example_facade_UserController_hpp */
