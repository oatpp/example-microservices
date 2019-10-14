
#ifndef example_facade_AppComponent_hpp
#define example_facade_AppComponent_hpp

#include "SwaggerComponent.hpp"

#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade {

class AppComponent {
private:
  v_int32 m_port;
  v_int32 m_userServicePort;
  v_int32 m_bookServicePort;
public:

  AppComponent(v_int32 port, v_int32 userServicePort, v_int32 bookServicePort)
    : m_port(port)
    , m_userServicePort(userServicePort)
    , m_bookServicePort(bookServicePort)
  {}

  /**
   *  Swagger component
   */
  SwaggerComponent swaggerComponent;

  /**
   * Create virtualhost interface
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)("facade" /* qualifier */, [] {
    return oatpp::network::virtual_::Interface::createShared("facade.virtualhost");
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider)("facade" /* qualifier */, [this] {
    return oatpp::network::server::SimpleTCPConnectionProvider::createShared(m_port);
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, virtualConnectionProvider)("facade.virtualhost" /* qualifier */, [this] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface, "facade" /* qualifier */);
    return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
  }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)("facade" /* qualifier */, [] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)("facade" /* qualifier */, [] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

};

}}

#endif /* example_facade_AppComponent_hpp */
