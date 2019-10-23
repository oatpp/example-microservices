
#include "book-service/AppComponent.hpp"
#include "book-service/Runner.hpp"

#include "user-service/AppComponent.hpp"
#include "user-service/Runner.hpp"

#include "facade/AppComponent.hpp"
#include "facade/Runner.hpp"

void run() {

  example::user::AppComponent userComponents(
    {"localhost", 8001},      // User Service
    {"user.virtualhost", 0}   // User Service Virtual Host
  );

  example::book::AppComponent bookComponents(
    {"localhost", 8002},      // Book Service
    {"book.virtualhost", 0}   // Book Service Virtual Host
  );

  example::facade::AppComponent facadeComponents(
    {"localhost", 8000}, // Facade service (this)
    //{"localhost", 8001}, // User Service
    //{"localhost", 8002}  // Book Service
    {"user.virtualhost", 0}, // User Service
    {"book.virtualhost", 0}  // Book Service
  );

  std::list<std::thread> acceptingThreads;

  example::user::Runner userRunner;
  userRunner.run(acceptingThreads);

  example::book::Runner bookRunner;
  bookRunner.run(acceptingThreads);

  example::facade::Runner facadeRunner;
  facadeRunner.run(acceptingThreads);

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
