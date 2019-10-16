
#ifndef example_book_db_model_Book_hpp
#define example_book_db_model_Book_hpp

#include "oatpp/core/Types.hpp"

#include <string>
#include <list>

namespace example { namespace book { namespace db { namespace model {

/**
 *  Object of Book stored in the Demo-Database
 */
class Book {
public:
  v_int64 id;
  v_int64 authorId;
  oatpp::String title;
};

}}}}

#endif /* example_book_db_model_Book_hpp */
