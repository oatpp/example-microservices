
#include "book-service/AppComponent.hpp"
#include "book-service/Runner.hpp"

void run() {

  /* Register Components in scope of run() method */
  example::book::AppComponent components(
    {"localhost", 8002},      // Book Service
    {"book.virtualhost", 0}   // Book Service Virtual Host
  );

  /* run */
  std::list<std::thread> acceptingThreads;
  example::book::Runner::run(acceptingThreads);

  for(auto& thread : acceptingThreads) {
    thread.join();
  }

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
}
