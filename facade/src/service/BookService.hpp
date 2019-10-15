#ifndef example_facade_example_bookService
#define example_facade_example_bookService

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace service {

#include OATPP_CODEGEN_BEGIN(ApiClient)

class BookService : public oatpp::web::client::ApiClient {
public:

  API_CLIENT_INIT(BookService)

  API_CALL("GET", "/books", getBooks)
  API_CALL("GET", "/books/{bookId}", getBookById, PATH(Int64, bookId))

};

#include OATPP_CODEGEN_END(ApiClient)

}}}

#endif //example_facade_example_bookService
