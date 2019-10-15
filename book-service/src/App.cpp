
#include "Runner.hpp"

void run() {

  auto interface = oatpp::network::virtual_::Interface::createShared("book-service.virtualhost");
  example::book::Runner::run(8002, interface);

}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  
  return 0;
}
