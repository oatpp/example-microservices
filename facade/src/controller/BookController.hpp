#ifndef example_facade_BookController_hpp
#define example_facade_BookController_hpp

#include "Constants.hpp"

#include "dto/BookInfoDto.hpp"
#include "dto/BookDto.hpp"
#include "dto/UserDto.hpp"

#include "service/BookService.hpp"
#include "service/UserService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade { namespace controller {

class BookController : public oatpp::web::server::api::ApiController {
private:

  OATPP_COMPONENT(std::shared_ptr<service::UserService>, userService, Qualifiers::SERVICE_FACADE);
  OATPP_COMPONENT(std::shared_ptr<service::BookService>, bookService, Qualifiers::SERVICE_FACADE);

public:

  BookController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper, Qualifiers::SERVICE_FACADE) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) {}

public:

/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

  ENDPOINT_INFO(getBookById) {
    // general
    info->summary = "Get one Book by bookId";
    info->addResponse<dto::BookInfoDto::ObjectWrapper>(Status::CODE_200, "application/json");
    info->addResponse<String>(Status::CODE_404, "text/plain");
    // params specific
    info->pathParams["bookId"].description = "Book Identifier";
  }
  ENDPOINT("GET", "/books/{bookId}", getBookById,
           PATH(Int64, bookId)) {

    auto response = bookService->getBookById(bookId);
    OATPP_ASSERT_HTTP(response->getStatusCode() == 200, Status::CODE_500, "Unable to get book by id");

    auto book = response->readBodyToDto<dto::BookDto>(getDefaultObjectMapper().get());

    response = userService->getUserById(book->authorId);
    OATPP_ASSERT_HTTP(response->getStatusCode() == 200, Status::CODE_500, "Unable to get user by id");

    auto user = response->readBodyToDto<dto::UserDto>(getDefaultObjectMapper().get());

    auto bookInfoDto = dto::BookInfoDto::createShared();
    bookInfoDto->id = book->id;
    bookInfoDto->title = book->title;
    bookInfoDto->author = user;

    return createDtoResponse(Status::CODE_200, bookInfoDto);

  }


//  ENDPOINT_INFO(getBooks) {
//    info->summary = "get all stored books";
//    info->addResponse<List<dto::BookDto::ObjectWrapper>::ObjectWrapper>(Status::CODE_200, "application/json");
//  }
//  ENDPOINT("GET", "/books", getBooks) {
//    return createDtoResponse(Status::CODE_200, m_database->getBooks());
//  }

/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)

};

}}}

#endif /* example_facade_BookController_hpp */
