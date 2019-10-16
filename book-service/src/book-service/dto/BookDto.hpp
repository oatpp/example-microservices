
#ifndef example_book_dto_BookDto_hpp
#define example_book_dto_BookDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace book { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(BookDto, Object)

  DTO_FIELD(Int64, id);
  DTO_FIELD(Int64, authorId, "authorId");
  DTO_FIELD(String, title, "title");

public:

  static BookDto::ObjectWrapper create(v_int64 id, v_int64 authorId, const String& title) {

    auto dto = BookDto::createShared();

    dto->id = id;
    dto->authorId = authorId;
    dto->title = title;

    return dto;

  }

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_book_dto_BookDto_hpp */
