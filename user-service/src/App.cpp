
#include "Runner.hpp"

void run() {

  auto interface = oatpp::network::virtual_::Interface::createShared("user-service.virtualhost");
  example::user::Runner::run(8000, interface);

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
}
