
#include "Runner.hpp"

#include "AppComponent.hpp"

#include "controller/BookController.hpp"
#include "controller/UserController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/server/Server.hpp"

#include <list>
#include <thread>

namespace example { namespace facade {

void Runner::run() {

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /**************************************************************/
  /* Create controllers and add endpoints to router             */

  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  auto userController = std::make_shared<controller::UserController>();
  userController->addEndpointsToRouter(router);

  auto bookController = std::make_shared<controller::BookController>();
  bookController->addEndpointsToRouter(router);

  docEndpoints->pushBackAll(userController->getEndpoints());
  docEndpoints->pushBackAll(bookController->getEndpoints());

  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
  swaggerController->addEndpointsToRouter(router);

  /**************************************************************/

  /* Create connection handler */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  std::list<std::thread> threads;

  threads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_FACADE);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    server.run();

  }));

  //OATPP_LOGI("facade", "server is listening on port '%hu'", port);


  threads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, "facade.virtualhost" /* qualifier */);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    server.run();

  }));

  //OATPP_LOGI("facade", "server is listening on virtual interface '%s'", interface->getName()->getData());


  for(auto& thread : threads) {
    thread.join();
  }

}

}}
