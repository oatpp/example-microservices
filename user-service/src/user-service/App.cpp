
#include "user-service/AppComponent.hpp"
#include "user-service/Runner.hpp"

void run() {

  /* Register Components in scope of run() method */
  example::user::AppComponent components(
    {"localhost", 8001},      // User Service
    {"user.virtualhost", 0}   // User Service Virtual Host
  );

  /* run */
  std::list<std::thread> acceptingThreads;
  example::user::Runner runner;
  runner.run(acceptingThreads);

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

