
#ifndef example_facade_dto_BookInfoDto_hpp
#define example_facade_dto_BookInfoDto_hpp

#include "UserDto.hpp"

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class BookInfoDto : public oatpp::DTO {

  DTO_INIT(BookInfoDto, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, title, "title");
  DTO_FIELD(UserDto, author);

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_facade_dto_BookInfoDto_hpp */