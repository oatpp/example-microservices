
#ifndef example_user_Runner_hpp
#define example_user_Runner_hpp

#include "AppComponent.hpp"

#include <list>
#include <thread>

namespace example { namespace user {

class Runner {
public:

  static void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_user_Runner_hpp
