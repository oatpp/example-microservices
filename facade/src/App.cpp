
#include "AppComponent.hpp"
#include "Runner.hpp"

void run() {

  /* Register Components in scope of run() method */
  example::facade::AppComponent components(
    {"localhost", 8000}, // Facade service (this)
    {"localhost", 8001}, // User Service
    {"localhost", 8002}  // Book Service
  );

  /* run */
  example::facade::Runner::run();

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
}
