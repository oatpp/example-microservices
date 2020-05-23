
#ifndef example_user_dto_UserDto_hpp
#define example_user_dto_UserDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace user { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::DTO {

  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, name, "name");

public:

  UserDto(v_int64 pId, const String& pName)
    : id(pId)
    , name(pName)
  {}

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_user_dto_UserDto_hpp */
