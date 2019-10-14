
#include "AppComponent.hpp"
#include "Runner.hpp"

void run() {

  /* Register Components in scope of run() method */
  example::facade::AppComponent components(8000, 0, 0);

  /* run */
  example::facade::Runner::run();

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
}
