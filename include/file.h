#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <streambuf>
#include <filesystem>
#include <iostream>
#include <memory>
#include <limits>
#include <stdexcept>

template <typename T>
struct zallocator {
 public:
  using value_type = T ;
  using pointer = value_type* ;
  using const_pointer = const value_type* ;
  using reference = value_type& ;
  using const_reference = const value_type& ;
  using size_type = std::size_t ;
  using difference_type = std::ptrdiff_t ;

  pointer address(reference v) const { return &v; }
  const_pointer address(const_reference v) const { return &v; }

  pointer allocate(size_type n, const void* hint = 0) {
    if (n > std::numeric_limits<size_type>::max() / sizeof(T))
      throw std::bad_alloc();
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, size_type n) {
    ::operator delete(p);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  template <typename U>
  struct rebind {
    typedef zallocator<U> other;
  };

  void construct(pointer ptr, const T& val) {
    new (static_cast<T*>(ptr)) T(val);
  }

  void destroy(pointer ptr) { static_cast<T*>(ptr)->~T(); }

#if __cpluplus >= 201103L
  template <typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    ::new (static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U* ptr) {
    ptr->~U();
  }
#endif
};

using byte = unsigned char ;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
    secure_string;

class pathStringHandler {
 public:
  pathStringHandler() = default;

  static void stringToFile( secure_string& fileContent,  std::string& filePath);
  static secure_string filePathToString( std::string& filePath);
 private:
  pathStringHandler(pathStringHandler const&) = delete;
  pathStringHandler& operator=(pathStringHandler const&) = delete; 
};

#endif // FILE_H_
