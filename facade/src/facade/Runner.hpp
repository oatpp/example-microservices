
#ifndef example_facade_Runner_hpp
#define example_facade_Runner_hpp

#include "oatpp/web/server/api/ApiController.hpp"

#include <list>
#include <thread>

namespace example { namespace facade {

class Runner {
private:
  std::list<std::shared_ptr<oatpp::web::server::api::ApiController>> m_controllers;
public:

  Runner();

  void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_facade_Runner_hpp
