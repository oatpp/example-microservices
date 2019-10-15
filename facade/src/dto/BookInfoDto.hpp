
#ifndef example_facade_dto_BookInfoDto_hpp
#define example_facade_dto_BookInfoDto_hpp

#include "./UserDto.hpp"

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookInfoDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(BookInfoDto, Object)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, title, "title");
  DTO_FIELD(UserDto::ObjectWrapper, author);

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_facade_dto_BookInfoDto_hpp */