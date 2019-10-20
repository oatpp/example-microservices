
#include "Runner.hpp"

#include "AppComponent.hpp"

#include "controller/BookController.hpp"
#include "controller/UserController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/server/Server.hpp"

namespace example { namespace facade {

Runner::Runner() {

  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_FACADE);

  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  auto userController = std::make_shared<controller::UserController>();
  userController->addEndpointsToRouter(router);
  m_controllers.push_back(userController);

  auto bookController = std::make_shared<controller::BookController>();
  bookController->addEndpointsToRouter(router);
  m_controllers.push_back(bookController);

  docEndpoints->pushBackAll(userController->getEndpoints());
  docEndpoints->pushBackAll(bookController->getEndpoints());

  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, documentInfo, Qualifiers::SERVICE_FACADE);
  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, resources, Qualifiers::SERVICE_FACADE);
  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints, documentInfo, resources);
  swaggerController->addEndpointsToRouter(router);
  m_controllers.push_back(swaggerController);

}

void Runner::run(std::list<std::thread>& acceptingThreads) {

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_FACADE);

  /* Create connection handler */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_FACADE);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("facade", "server is listening on port '%s'", connectionProvider->getProperty("port").getData());
    server.run();

  }));


  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_FACADE_VH);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("facade", "server is listening on virtual interface '%s'", connectionProvider->getProperty("host").getData());
    server.run();

  }));

}

}}