
#ifndef example_facade_dto_UserDto_hpp
#define example_facade_dto_UserDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace facade { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(UserDto, Object)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, name, "name");

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_facade_dto_UserDto_hpp */
