
#ifndef example_facade_AppComponent_hpp
#define example_facade_AppComponent_hpp

#include "SwaggerComponent.hpp"

#include "service/UserService.hpp"
#include "service/BookService.hpp"

#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/client/ConnectionProvider.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"
#include "oatpp/network/client/SimpleTCPConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade {

struct HostPort {
  oatpp::String host;
  v_word16 port;
};

class AppComponent {
private:
  HostPort m_facade;
  HostPort m_userService;
  HostPort m_bookService;
public:

  AppComponent(const HostPort& facade, const HostPort& userService, const HostPort& bookService)
    : m_facade(facade)
    , m_userService(userService)
    , m_bookService(bookService)
  {}

  /**
   * Swagger component
   */
  SwaggerComponent swaggerComponent;

  /**
   * Create virtualhost interface
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)(Qualifiers::SERVICE_FACADE, [] {
    return oatpp::network::virtual_::Interface::obtainShared("facade.virtualhost");
  }());

  /**
   * Create "real-port" connection provider
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)(Qualifiers::SERVICE_FACADE, [this] {
    return oatpp::network::server::SimpleTCPConnectionProvider::createShared(m_facade.port);
  }());

  /**
   * Create "virtualhost" connection provider
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, virtualConnectionProvider)(Qualifiers::SERVICE_FACADE_VH, [] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface, Qualifiers::SERVICE_FACADE);
    return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
  }());

  /**
   * Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)(Qualifiers::SERVICE_FACADE, [] {
    return oatpp::web::server::HttpRouter::createShared();
  }());

  /**
   * Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper)(Qualifiers::SERVICE_FACADE, [] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

  /**
   * Create UserService component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<service::UserService>, userService)(Qualifiers::SERVICE_FACADE, [this] {

    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper, Qualifiers::SERVICE_FACADE);

    auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared(m_userService.host, m_userService.port);
    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
    return service::UserService::createShared(requestExecutor, objectMapper);

  }());

  /**
   * Create BookService component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<service::BookService>, bookService)(Qualifiers::SERVICE_FACADE, [this] {

    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper, Qualifiers::SERVICE_FACADE);

    auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared(m_bookService.host, m_bookService.port);
    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
    return service::BookService::createShared(requestExecutor, objectMapper);

  }());

};

}}

#endif /* example_facade_AppComponent_hpp */
