
#include "Runner.hpp"

#include "controller/BookController.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"

#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"
#include "oatpp/network/server/Server.hpp"

#include <list>
#include <thread>

namespace example { namespace book {

void Runner::run(v_word16 port, const std::shared_ptr<NetworkVirtualInterface>& interface) {


  /* Register Components in scope of run() method */
  example::book::AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /**************************************************************/
  /* Create controllers and add endpoints to router             */

  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();

  auto bookController = std::make_shared<controller::BookController>();
  bookController->addEndpointsToRouter(router);

  docEndpoints->pushBackAll(bookController->getEndpoints());

  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
  swaggerController->addEndpointsToRouter(router);

  /**************************************************************/

  /* Create connection handler */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  std::list<std::thread> threads;

  if(port > 0) {

    threads.push_back(std::thread([port, router, connectionHandler]{

      auto connectionProvider = oatpp::network::server::SimpleTCPConnectionProvider::createShared(port);
      oatpp::network::server::Server server(connectionProvider, connectionHandler);
      server.run();

    }));

    OATPP_LOGI("book-service", "server is listening on port '%hu'", port);

  }

  if(interface) {

    threads.push_back(std::thread([interface, router, connectionHandler]{

      auto connectionProvider = oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
      oatpp::network::server::Server server(connectionProvider, connectionHandler);
      server.run();

    }));

    OATPP_LOGI("book-service", "server is listening on virtual interface '%s'", interface->getName()->getData());

  }

  for(auto& thread : threads) {
    thread.join();
  }

}

}}
