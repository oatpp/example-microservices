
#ifndef example_book_Runner_hpp
#define example_book_Runner_hpp

#include "AppComponent.hpp"

#include <list>
#include <thread>

namespace example { namespace book {

class Runner {
public:

  static void run(std::list<std::thread>& acceptingThreads);

};

}}

#endif // example_book_Runner_hpp
