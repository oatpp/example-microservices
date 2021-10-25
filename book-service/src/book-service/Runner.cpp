
#include "Runner.hpp"

#include "AppComponent.hpp"

#include "controller/BookController.hpp"

#include "oatpp-swagger/Controller.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"

namespace example { namespace book {

Runner::Runner() {

  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_BOOK);

  oatpp::web::server::api::Endpoints docEndpoints;

  /* Add BookController */
  docEndpoints.append(router->addController(std::make_shared<controller::BookController>())->getEndpoints());

  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, documentInfo, Qualifiers::SERVICE_BOOK);
  OATPP_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, resources, Qualifiers::SERVICE_BOOK);

  router->addController(oatpp::swagger::Controller::createShared(docEndpoints, documentInfo, resources));

}

void Runner::run(std::list<std::thread>& acceptingThreads) {

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router, Qualifiers::SERVICE_BOOK);

  /* Create connection handler */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_BOOK);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("book-service", "server is listening on port '%s'", connectionProvider->getProperty("port").getData());
    server.run();

  }));

  acceptingThreads.push_back(std::thread([router, connectionHandler]{

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider, Qualifiers::SERVICE_BOOK_VH);
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGI("book-service", "server is listening on virtual interface '%s'", connectionProvider->getProperty("host").getData());
    server.run();

  }));

}

}}
