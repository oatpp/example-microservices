
#ifndef example_book_dto_BookDto_hpp
#define example_book_dto_BookDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace book { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::Object {

  DTO_INIT(BookDto, Object)

  DTO_FIELD(Int64, id);
  DTO_FIELD(Int64, authorId, "authorId");
  DTO_FIELD(String, title, "title");

public:

  BookDto(v_int64 pId, v_int64 pAuthorId, const String& pTitle)
    : id(pId)
    , authorId(pAuthorId)
    , title(pTitle)
  {}

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_book_dto_BookDto_hpp */
