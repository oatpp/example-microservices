
#ifndef example_facade_Runner_hpp
#define example_facade_Runner_hpp

#include <list>
#include <thread>

namespace example { namespace facade {

class Runner {
public:

  static void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_facade_Runner_hpp
