
#include "Runner.hpp"

#include "AppComponent.hpp"

#include "controller/UserController.hpp"

#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"

namespace example { namespace user {

Runner::Runner() {

  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_USER);

  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  /* Add BookController */
  auto userController = std::make_shared<controller::UserController>();
  userController->addEndpointsToRouter(router);
  m_controllers.push_back(userController);

  docEndpoints->pushBackAll(userController->getEndpoints());

  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, documentInfo, Qualifiers::SERVICE_USER);
  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, resources, Qualifiers::SERVICE_USER);
  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints, documentInfo, resources);
  swaggerController->addEndpointsToRouter(router);
  m_controllers.push_back(swaggerController);

}

void Runner::run(std::list<std::thread>& acceptingThreads) {

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_USER);

  /* Create connection handler */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_USER);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("user-service", "server is listening on port '%s'", connectionProvider->getProperty("port").getData());
    server.run();

  }));


  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_USER_VH);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("user-service", "server is listening on virtual interface '%s'", connectionProvider->getProperty("host").getData());
    server.run();

  }));

}

}}
