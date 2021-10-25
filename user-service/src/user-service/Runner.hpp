
#ifndef example_user_Runner_hpp
#define example_user_Runner_hpp

#include "oatpp/web/server/api/ApiController.hpp"

#include <list>
#include <thread>

namespace example { namespace user {

class Runner {
public:

  Runner();

  void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_user_Runner_hpp
