#pragma once

#include <memory>
#include <string>
#include <vector>

namespace stdx {

/** Extension of std::basic_string adding additional Python-like functionality
 
 Class inherits from std::basic_string so not as much needs to be implemented.
 
 \tparam CharT character type.
 \tparam Traits traits class specifying the operations on the character type
 \tparam Allocator Allocator type used to allocate internal storage
 */
template
< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
class basic_string : public std::basic_string<CharT, Traits, Allocator> {

  using parent_type = std::basic_string<CharT, Traits, Allocator>;
  
public:
  /* Member types */
  using traits_type = typename parent_type::traits_type;
  using value_type = typename parent_type::value_type;
  using allocator_type = typename parent_type::allocator_type;
  using size_type = typename parent_type::size_type;
  using difference_type = typename parent_type::difference_type;
  using reference = typename parent_type::reference;
  using const_reference = typename parent_type::const_reference;
  using pointer = typename parent_type::pointer;
  using const_pointer = typename parent_type::const_pointer;
  using iterator = typename parent_type::iterator;
  using const_iterator = typename parent_type::const_iterator;
  using reverse_iterator = typename parent_type::reverse_iterator;
  using const_reverse_iterator = typename parent_type::const_reverse_iterator;
  
  /* Static constants */
  static const size_type npos = parent_type::npos;
  // This constants may not work correctly for anything other than CharT = char
  static const basic_string whitespace() { return {0x20, 0x0c, 0x0a, 0x0d, 0x09, 0x0b, 0x0}; }
  static const basic_string lowercase() { return "abcdefghijklmnopqrstuvwxyz"; }
  static const basic_string uppercase() { return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
  static const basic_string digits() { return "0123456789"; }
  static const basic_string hexdigits() { return "0123456789ABCDEFabcdef"; }
  static const basic_string alpha() { return uppercase() + lowercase(); }
  static const basic_string alphanumeric() { return digits() + alpha(); }
  
  /* Constructors */
  /** Default constructor.
   *  Constructs empty string (zero size and unspecified cpacity). If no allocator is supplied, allocator is obtained from a default-constructed instance.
   */
  basic_string() noexcept(noexcept(Allocator()))
  : basic_string(Allocator()) { }
  explicit basic_string(const Allocator& alloc) noexcept
  : parent_type(alloc) { }
  
  /** Copy char constructor.
   *  Constructs the string with \p count copies of character \p ch. This constructor is not used for class template argument deduction of the Allocator type that would be deduced does not qqualify as an allocator.
   */
  basic_string(size_type count, CharT ch, const Allocator& alloc = Allocator())
  : parent_type(count, ch, alloc) { }
  
  /** Substring constructor.
   *  Constructs the string with a substring [\p pos, \p pos + \p count) of the other. If \p count == \p npos, if \p count is not specified, or if the requested substring lasts past the end of the string, the resulting substring is [\p pos, \p other.size()).
   */
  basic_string(const basic_string& other, size_type pos, const Allocator& alloc = Allocator())
  : parent_type(other, pos, alloc) { }
  basic_string(const parent_type& other, size_type pos, const Allocator& alloc = Allocator())
  : parent_type(other, pos, alloc) { }
  basic_string(const basic_string& other, size_type pos, size_type count, const Allocator& alloc = Allocator())
  : parent_type(other, pos, count, alloc) { }
  basic_string(const parent_type& other, size_type pos, size_type count, const Allocator& alloc = Allocator())
  : parent_type(other, pos, count, alloc) { }
  
  /** Raw substring constructor.
   *  Constructs the string with the first count characters of character string pointe to be \p s. \p s can contain null characters. The length of the string is \p count. The behaviour is undefined if [\p s, \p s + \p count) is not a valid range.
   */
  basic_string(const CharT* s, size_type count, const Allocator& alloc = Allocator())
  : parent_type(s, count, alloc) { }
  
  /** Raw string constructor.
   *  Constructs the string with the contents initialised with a copy of the null-terminated character string pointed to by \p s. The length of the string is determined by the first null character. The behaciour is undefined if [\p s, \p s + Traits::length(\p s)) is not a valid range (for example, if \p s is a null pointer). This constructor is not used for class template argument deduction if the Allocator type that would be deduced does not qualify as an allocator.
   */
  basic_string(const CharT* s, const Allocator& alloc = Allocator())
  : parent_type(s, alloc) { }
  
  /** Range constructor.
   *  Constructs the strong with the contents of the range [\p first, \p last). This constructor only participates in overload resolution if InputIt satisfies LegacyInputIterator.
   */
  template <class InputIt>
  basic_string(InputIt first, InputIt last, const Allocator& alloc = Allocator() )
  : parent_type(first, last, alloc) { }
  
  /** Copy constructor.
   *  Constructs the strong with a copy of the contents of \p other.
   */
  basic_string(const basic_string& other)
  : parent_type(other) { }
  basic_string(const parent_type& other)
  : parent_type(other) { }
  basic_string(const basic_string& other, const Allocator& alloc)
  : parent_type(other, alloc) { }
  basic_string(const parent_type& other, const Allocator& alloc)
  : parent_type(other, alloc) { }
  
  /** Move constructor.
   * Constructs the string with the contents of \p other using move semantics. \p other is left in valid, but unspecified state.
   */
  basic_string(basic_string&& other)
  : parent_type(std::move(other)) { }
  basic_string(parent_type&& other)
  : parent_type(std::move(other)) { }
  basic_string(basic_string&& other, const Allocator& alloc)
  : parent_type(std::move(other), alloc) { }
  basic_string(parent_type&& other, const Allocator& alloc)
  : parent_type(std::move(other), alloc) { }
  
  /** Initialiser list constructor.
   *  Constructs the string with the contents of the initialiser list \p ilist.
   */
  basic_string(std::initializer_list<CharT> ilist, const Allocator& alloc = Allocator())
  : parent_type(ilist, alloc) { }
  
  // Ignore string view constructors for now
  
  /** Destructor */
  ~basic_string() { }
  
  /* Assignment operators */
  using parent_type::operator=;
  /** Copy assignment.
   *  Replaces the contents with a copy of \p str. If \p *this and \p str are the same object, this function has no effect.
   */
  basic_string& operator=(const basic_string& str) {
    parent_type::operator=(str);
    return *this;
  }
  /** Move assignment.
   *  Replaces the contents with those of \p str using move semantics. \p str is in a valid but unspecified state afterwards. If std::allocator_traits<Allocator>::propagate_on_container_move_assignment() is true, the target allocator is replaced by a copy of the source allocator. If it is false and the source and the target allocators do not compare equal, the target cannot take ownership of the source memory and must assign each character individually, allocating additional memory using its own allocator as needed. Unlike other container move assignments, references, pointers, and iterators to str may be invalidated.
   */
  basic_string& operator=(basic_string&& str)
  noexcept(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
           || std::allocator_traits<Allocator>::is_always_equal::value) {
    parent_type::operator=(std::move(str));
    return *this;
  }
  
  /* Override methods to enable return of stdx::basic_string, not std::basic_string.
   * Useful for chaining operations together. */
  /** Extract a substring.
   *  Returns a substring [\p pos, \p pos +\p count). If the requested substring extends past the end of the string, or if \p count == \p npos, the returned substring is [\p pos, size()).
   */
  basic_string substr(size_type pos = 0, size_type count = npos) const {
    return parent_type::substr(pos, count);
  }
  
  /* New string operations */
  /* Stripping white space from the ends. */
  basic_string lstrip(const basic_string& chars = whitespace()) const {
    size_type pos = this->find_first_not_of(chars);
    return (pos == npos) ? basic_string() : basic_string(this->begin() + pos, this->end());
  }
  basic_string rstrip(const basic_string& chars = whitespace()) const {
    size_type pos = this->find_last_not_of(chars);
    return (pos == npos) ? basic_string() : basic_string(this->begin(), this->begin() + pos + 1);
  }
  basic_string strip(const basic_string& chars = whitespace()) const {
    size_type left = this->find_first_not_of(chars);
    size_type right = this->find_last_not_of(chars);
    // If left == npos, then right will be too
    return (left == npos) ? basic_string() : basic_string(this->begin() + left, this->begin() + right + 1);
  }
  basic_string& lstrip_inplace(const basic_string& chars = whitespace()) {
    size_type pos = this->find_first_not_of(chars);
    (pos == npos) ? this->erase(this->begin(), this->end()) : this->erase(this->begin(), this->begin() + pos);
    return *this;
  }
  basic_string& rstrip_inplace(const basic_string& chars = whitespace()) {
    size_type pos = this->find_last_not_of(chars);
    (pos == npos) ? this->erase(this->begin(), this->end()) : this->erase(this->begin() + pos + 1, this->end());
    return *this;
  }
  basic_string& strip_inplace(const basic_string& chars = whitespace()) {
    size_type right = this->find_last_not_of(chars);
    // If right == npos, then left will be too
    if (right == npos) {
      this->erase(this->begin(), this->end());
    } else {
      this->resize(right + 1);
      size_type left = this->find_first_not_of(chars);
      this->erase(this->begin(), this->begin() + left);
    }
    return *this;
  }
  /* Join iterable for strings together using copies of this. */
  template <typename InputIt>
  basic_string join(InputIt first, InputIt last) const {
    basic_string result;
    size_type num_joiners = std::distance(first, last) - 1;
    result.reserve(num_joiners * this->size() + 10 * (num_joiners + 1));
    while (first != last) {
      result.append(*first);
      if (num_joiners--) { result.append(*this); }
      ++num_joiners;
    }
    result.shrink_to_fit();
    return result;
  }
  
};

/** Typedefs for common character types **/
using string = basic_string<char>;
using wstring = basic_string<wchar_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;

}
