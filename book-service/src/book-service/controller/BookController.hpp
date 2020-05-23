#ifndef example_book_BookController_hpp
#define example_book_BookController_hpp

#include "book-service/Constants.hpp"
#include "book-service/db/Database.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace book { namespace controller {

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- codegen Begin

class BookController : public oatpp::web::server::api::ApiController {
private:

  /**
   *  Inject Database component
   */
  OATPP_COMPONENT(std::shared_ptr<db::Database>, m_database, Qualifiers::SERVICE_BOOK);

public:

  BookController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper, Qualifiers::SERVICE_BOOK) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

  ENDPOINT_INFO(createBook) {
    info->summary = "Create new Book";
    info->addConsumes<Object<dto::BookDto>>("application/json");
    info->addResponse<Object<dto::BookDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("POST", "/books", createBook,
           BODY_DTO(Object<dto::BookDto>, bookDto)) {
    OATPP_ASSERT_HTTP(bookDto->authorId, Status::CODE_400, "'authorId' is require!");
    return createDtoResponse(Status::CODE_200, m_database->createBook(bookDto));
  }


  ENDPOINT_INFO(putBook) {
    // general
    info->summary = "Update Book by bookId";
    info->addConsumes<Object<dto::BookDto>>("application/json");
    info->addResponse<Object<dto::BookDto>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["bookId"].description = "Book Identifier";
  }
  ENDPOINT("PUT", "/books/{bookId}", putBook,
           PATH(Int64, bookId),
           BODY_DTO(Object<dto::BookDto>, bookDto)) {
    bookDto->id = bookId;
    return createDtoResponse(Status::CODE_200, m_database->updateBook(bookDto));
  }


  ENDPOINT_INFO(getBookById) {
    // general
    info->summary = "Get one Book by bookId";
    info->addResponse<Object<dto::BookDto>>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["bookId"].description = "Book Identifier";
  }
  ENDPOINT("GET", "/books/{bookId}", getBookById,
           PATH(Int64, bookId)) {
    auto book = m_database->getBookById(bookId);
    OATPP_ASSERT_HTTP(book, Status::CODE_404, "Book not found");
    return createDtoResponse(Status::CODE_200, book);
  }


  ENDPOINT_INFO(getBooks) {
    info->summary = "get all stored books";
    info->addResponse<List<Object<dto::BookDto>>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/books", getBooks) {
    return createDtoResponse(Status::CODE_200, m_database->getBooks());
  }


  ENDPOINT_INFO(deleteBook) {
    // general
    info->summary = "Delete Book by bookId";
    info->addResponse<String>(Status::CODE_200, "text/plain");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["bookId"].description = "Book Identifier";
  }
  ENDPOINT("DELETE", "/books/{bookId}", deleteBook,
           PATH(Int64, bookId)) {
    bool success = m_database->deleteBook(bookId);
    OATPP_ASSERT_HTTP(success, Status::CODE_404, "Book not deleted. Perhaps no such Book in the Database");
    return createResponse(Status::CODE_200, "Book successfully deleted");
  }

};

#include OATPP_CODEGEN_END(ApiController) //<-- codegen End

}}}

#endif /* example_book_BookController_hpp */
