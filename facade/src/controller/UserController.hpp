#ifndef example_facade_UserController_hpp
#define example_facade_UserController_hpp

#include "Constants.hpp"

#include "dto/UserDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/data/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade { namespace controller {

class UserController : public oatpp::web::server::api::ApiController {
public:

  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper, Qualifiers::SERVICE_FACADE) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)


/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)

};

}}}

#endif /* example_facade_UserController_hpp */
