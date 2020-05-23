
#ifndef example_facade_dto_BookDto_hpp
#define example_facade_dto_BookDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::DTO {

  DTO_INIT(BookDto, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(Int64, authorId, "authorId");
  DTO_FIELD(String, title, "title");

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_facade_dto_BookDto_hpp */
