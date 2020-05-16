
#include "Database.hpp"

namespace example { namespace book { namespace db {

model::Book Database::serializeFromDto(const dto::BookDto::ObjectWrapper &bookDto) {
  model::Book book;
  if (bookDto->id) {
    book.id = bookDto->id;
  }
  book.title = bookDto->title;
  book.authorId = bookDto->authorId;
  return book;
}

dto::BookDto::ObjectWrapper Database::deserializeToDto(const model::Book &book) {
  auto dto = dto::BookDto::createShared();
  dto->id = book.id;
  dto->title = book.title;
  dto->authorId = book.authorId;
  return dto;
}

dto::BookDto::ObjectWrapper Database::createBook(const dto::BookDto::ObjectWrapper &bookDto) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto book = serializeFromDto(bookDto);
  book.id = m_idCounter++;
  m_booksById[book.id] = book;
  return deserializeToDto(book);
}

dto::BookDto::ObjectWrapper Database::updateBook(const dto::BookDto::ObjectWrapper &bookDto) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto book = serializeFromDto(bookDto);
  if (book.id < 0) {
    throw std::runtime_error("Book Id cannot be less than 0");
  }
  auto it = m_booksById.find(book.id);
  if (it != m_booksById.end()) {
    m_booksById[book.id] = book;
  } else {
    throw new std::runtime_error("Such book not found");
  }
  return deserializeToDto(book);
}

dto::BookDto::ObjectWrapper Database::getBookById(v_int64 id) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto it = m_booksById.find(id);
  if (it == m_booksById.end()) {
    return nullptr;
  }
  return deserializeToDto(it->second);
}

oatpp::data::mapping::type::List<dto::BookDto::ObjectWrapper>::ObjectWrapper Database::getBooks() {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto result = oatpp::data::mapping::type::List<dto::BookDto::ObjectWrapper>::createShared();
  auto it = m_booksById.begin();
  while (it != m_booksById.end()) {
    result->push_back(deserializeToDto(it->second));
    it++;
  }
  return result;
}

bool Database::deleteBook(v_int64 id) {
  std::lock_guard<oatpp::concurrency::SpinLock> lock(m_lock);
  auto it = m_booksById.find(id);
  if (it == m_booksById.end()) {
    return false;
  }
  m_booksById.erase(it);
  return true;
}

}}}
