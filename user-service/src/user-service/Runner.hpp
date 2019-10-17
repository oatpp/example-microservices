
#ifndef example_user_Runner_hpp
#define example_user_Runner_hpp

#include "oatpp/web/server/api/ApiController.hpp"

#include <list>
#include <thread>

namespace example { namespace user {

class Runner {
private:
  std::list<std::shared_ptr<oatpp::web::server::api::ApiController>> m_controllers;
public:

  Runner();

  void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_user_Runner_hpp
