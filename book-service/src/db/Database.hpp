
#ifndef example_book_db_Database_hpp
#define example_book_db_Database_hpp

#include "dto/BookDto.hpp"
#include "db/model/Book.hpp"

#include "oatpp/core/concurrency/SpinLock.hpp"
#include <unordered_map>

namespace example { namespace book { namespace db {

/**
 *  Trivial in-memory Database based on unordered_map container.
 *  For demo purposes only :)
 */
class Database {
private:
  oatpp::concurrency::SpinLock m_lock;
  v_int64 m_idCounter; ///< counter to generate bookIds
  std::unordered_map<v_int64, model::Book> m_booksById; ///< Map bookId to Book
private:
  model::Book serializeFromDto(const dto::BookDto::ObjectWrapper& bookDto);
  dto::BookDto::ObjectWrapper deserializeToDto(const model::Book& book);
public:
  
  Database()
    : m_idCounter(1)
  {

    /* Prepopulate Database */

    createBook(dto::BookDto::create(0, 1, "The Great Gatsby"));
    createBook(dto::BookDto::create(0, 2, "To Kill a Mockingbird"));
    createBook(dto::BookDto::create(0, 3, "Harry Potter and the Sorcerer's Stone"));
    createBook(dto::BookDto::create(0, 4, "1984"));
    createBook(dto::BookDto::create(0, 5, "The Catcher in the Rye"));

  }
  
  dto::BookDto::ObjectWrapper createBook(const dto::BookDto::ObjectWrapper& bookDto);
  dto::BookDto::ObjectWrapper updateBook(const dto::BookDto::ObjectWrapper& bookDto);
  dto::BookDto::ObjectWrapper getBookById(v_int64 id);
  oatpp::data::mapping::type::List<dto::BookDto::ObjectWrapper>::ObjectWrapper getBooks();
  bool deleteBook(v_int64 id);
  
};

}}}

#endif /* example_book_db_Database_hpp */
