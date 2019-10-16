
#include "Runner.hpp"

#include "AppComponent.hpp"

#include "controller/BookController.hpp"

#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/server/Server.hpp"

namespace example { namespace book {

void Runner::run(std::list<std::thread>& acceptingThreads) {

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

  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_BOOK);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("book-service", "server is listening on port '%s'", connectionProvider->getProperty("port").getData());
    server.run();

  }));


  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_BOOK_VH);
    oatpp::network::server::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("book-service", "server is listening on virtual interface '%s'", connectionProvider->getProperty("host").getData());
    server.run();

  }));

}

}}
