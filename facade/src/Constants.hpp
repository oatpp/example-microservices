
#ifndef example_facade_Constants_hpp
#define example_facade_Constants_hpp

namespace example { namespace facade {

class Qualifiers {
public:

  static constexpr const char* SERVICE_FACADE = "facade";
  static constexpr const char* SERVICE_BOOK = "book-service";
  static constexpr const char* SERVICE_USER = "user-service";

  static constexpr const char* SERVICE_FACADE_VH = "facade.virtualhost";
  static constexpr const char* SERVICE_BOOK_VH = "book-service.virtualhost";
  static constexpr const char* SERVICE_USER_VH = "user-service.virtualhost";

};

}}

#endif // example_facade_Constants_hpp
