
#ifndef example_user_AppComponent_hpp
#define example_user_AppComponent_hpp

#include "user-service/db/Database.hpp"

#include "Constants.hpp"

#include "SwaggerComponent.hpp"

#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

namespace example { namespace user {

struct HostPort {
  oatpp::String host;
  v_word16 port;
};


class AppComponent {
private:
  HostPort m_hostPort;
  HostPort m_virtualHost;
public:

  AppComponent(const HostPort& hostPort, const HostPort& virtualHost)
    : m_hostPort(hostPort)
    , m_virtualHost(virtualHost)
  {}

  /**
   *  Swagger component
   */
  SwaggerComponent swaggerComponent;

  /**
   * Create virtualhost interface
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)(Qualifiers::SERVICE_USER, [this] {
    return oatpp::network::virtual_::Interface::obtainShared(m_virtualHost.host);
  }());

  /**
   * Create "real-port" connection provider
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)(Qualifiers::SERVICE_USER, [this] {
    return oatpp::network::server::SimpleTCPConnectionProvider::createShared(m_hostPort.port);
  }());

  /**
   * Create "virtualhost" connection provider
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, virtualConnectionProvider)(Qualifiers::SERVICE_USER_VH, [] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface, Qualifiers::SERVICE_USER);
    return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
  }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)(Qualifiers::SERVICE_USER, [] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)(Qualifiers::SERVICE_USER, [] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

  /**
   *  Create Demo-Database component which stores information about users
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<db::Database>, database)(Qualifiers::SERVICE_USER, [] {
    return std::make_shared<db::Database>();
  }());

};

}}

#endif /* example_user_AppComponent_hpp */
