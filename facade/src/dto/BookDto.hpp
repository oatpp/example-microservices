
#ifndef example_facade_dto_BookDto_hpp
#define example_facade_dto_BookDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(BookDto, Object)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, title, "title");
  DTO_FIELD(String, author, "author");

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_facade_dto_BookDto_hpp */
