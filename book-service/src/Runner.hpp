
#ifndef example_book_Runner_hpp
#define example_book_Runner_hpp

#include "AppComponent.hpp"

#include "oatpp/network/virtual_/Interface.hpp"


namespace example { namespace book {

class Runner {
private:
  typedef oatpp::network::virtual_::Interface NetworkVirtualInterface;
public:

  static void run(v_word16 port, const std::shared_ptr<NetworkVirtualInterface>& interface);

};

}}

#endif // example_book_Runner_hpp
