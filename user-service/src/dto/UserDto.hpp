
#ifndef example_user_dto_UserDto_hpp
#define example_user_dto_UserDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace example { namespace user { namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

class UserDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(UserDto, Object)

  DTO_FIELD(Int64, id);
  DTO_FIELD(String, name, "name");

public:

  static UserDto::ObjectWrapper create(v_int64 id, const String& name) {

    auto dto = createShared();

    dto->id = id;
    dto->name = name;

    return dto;

  }

};

#include OATPP_CODEGEN_END(DTO)

}}}

#endif /* example_user_dto_UserDto_hpp */
