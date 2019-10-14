
#ifndef example_user_AppComponent_hpp
#define example_user_AppComponent_hpp

#include "db/Database.hpp"

#include "SwaggerComponent.hpp"

#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

namespace example { namespace user {

class AppComponent {
public:

  /**
   *  Swagger component
   */
  SwaggerComponent swaggerComponent;

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

  /**
   *  Create Demo-Database component which stores information about users
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<db::Database>, database)([] {
    return std::make_shared<db::Database>();
  }());

};

}}

#endif /* example_user_AppComponent_hpp */
