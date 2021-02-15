#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <vector>

namespace stdx {

/** Fixed vector class. Is a dynamic vector that is size constrained at construction/resize time. Can have negative indices as defined at construction time.
 */
template <class T, class Allocator = std::allocator<T>>
class fixed_vector {
  using base_type = std::vector<T, Allocator>;
public:
  /* Member types */
  using value_type = typename base_type::value_type;
  using allocator_type = typename base_type::value_type;
  using size_type = typename base_type::size_type;
  using difference_type = typename base_type::difference_type;
  using reference = typename base_type::reference;
  using const_reference = typename base_type::const_reference;
  using pointer = typename base_type::pointer;
  using const_pointer = typename base_type::pointer;
  using iterator = typename base_type::iterator;
  using const_iterator = typename base_type::const_iterator;
  using reverse_iterator = typename base_type::reverse_iterator;
  using const_reverse_iterator = typename base_type::const_reverse_iterator;
  
  /* Constructors */
  /** Default constructor.
   *  Constructs a vector which cannot be filled, as it has zero range.
   */
  fixed_vector() noexcept(noexcept(Allocator())): elems(), minindex(0), maxindex(0) { }
  explicit fixed_vector(const Allocator& alloc) noexcept : elems(alloc), minindex(0), maxindex(0) { }
  
  /** Construct the container with copies of \p value in the range \p min to \p max. */
  fixed_vector(int64_t min, int64_t max, const T& value, const Allocator& alloc = Allocator())
  : elems(max > min ? max - min + 1 : 0, value, alloc), minindex(min), maxindex(max) {
    if (max <= min) { throw std::range_error("Invalid construction range."); }
  }
  /** Construct the container with default-inserted instances of T in the range \p min to \p max. */
  fixed_vector(int64_t min, int64_t max, const Allocator& alloc = Allocator())
  : elems(max > min ? max - min + 1 : 0, alloc), minindex(min), maxindex(max) {
    if (max <= min) { throw std::range_error("Invalid construction range."); }
  }
  /** Construct with contents of the range [\p first, \p last). \p maxindex is calculated based on the construction range. */
  template <class InputIt>
  fixed_vector(int64_t min, InputIt first, InputIt last, const Allocator& alloc = Allocator())
  : elems(first, last, alloc), minindex(min), maxindex(min + std::distance(first, last)) { }
  
  /** Copy constructor */
  fixed_vector(const fixed_vector& other)
  : elems(other.elems), minindex(other.minindex), maxindex(other.maxindex) { }
  fixed_vector(const fixed_vector& other, const Allocator& alloc)
  : elems(other.elems, alloc), minindex(other.minindex), maxindex(other.maxindex) { }
  
  /** Move constructor */
  fixed_vector(fixed_vector&& other) noexcept
  : elems(std::move(other.elems)), minindex(other.index), maxindex(other.index) { }
  fixed_vector(fixed_vector&& other, const Allocator& alloc)
  : elems(std::move(other.elems), alloc), minindex(other.index), maxindex(other.index) { }
  
  /** Initialiser list constructor. */
  fixed_vector(int64_t min, std::initializer_list<T> init, const Allocator& alloc = Allocator())
  : elems(init, alloc), minindex(min), maxindex(min + init.size()) { }
  
  /** Destructor. */
  ~fixed_vector() { }
  
  /** Assignment opearators. */
  fixed_vector& operator=(const fixed_vector& other) {
    if (&other != this) {
      elems = other.elems;
      minindex = other.minindex;
      maxindex = other.maxindex;
    }
    return *this;
  }
  fixed_vector& operator=(fixed_vector&& other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value
                                                         || std::allocator_traits<Allocator>::is_always_equal::value) {
    if (&other != this) {
      elems = std::move(other.elems);
      minindex = std::move(other.minindex);
      maxindex = std::move(other.maxindex);
    }
    return *this;
  }
  // No initializer list assignment
  
  /** Replace the contents with copies of \p value. */
  void assign(int64_t min, int64_t max, const T& value) {
    if (max <= min) { throw std::range_error("Invalid assign range."); }
    elems.assign(max - min + 1, value);
    minindex = min;
    maxindex = max;
  }
  template <class InputIt>
  void assign(int64_t min, InputIt first, InputIt last) {
    elems.assign(first, last);
    minindex = min;
    maxindex = min + elems.size();
  }
  void assign(int64_t min, std::initializer_list<T> ilist) {
    elems.assign(ilist);
    minindex = min;
    maxindex = min + elems.size();
  }
  
  /** Returns the allocator associated with the container. */
  allocator_type get_allocator() const noexcept { return elems.get_allocator(); }
  
  /** Return a reference to the element at specified location \p pos, with bounds checking. If \p pos is not within the range of the container, an exception of type std::out_of_range is thrown. */
  reference at(int64_t pos) {
    if (pos < minindex || pos > maxindex) { throw std::out_of_range("fixed_vector::at"); }
    return elems.at(pos - minindex);
  }
  const_reference at(int64_t pos) const {
    if (pos < minindex || pos > maxindex) { throw std::out_of_range("fixed_vector::at"); }
    return elems.at(pos - minindex);
  }
  
  /** Returns a reference to the element at specified location pos. No bounds checking is performed. */
  reference operator[](int64_t pos) { return elems[pos - minindex]; }
  const_reference operator[](int64_t pos) const { return elems[pos - minindex]; }
  
  /** Returns a reference to the first element in the container. Calling front on an empty container is undefined. */
  reference front() { return elems.front(); }
  const_reference front() const { return elems.front(); }
  
  /** Returns a reference to the last element in the container. Calling back on an empty container causes undefined behaviour. */
  reference back() { return elems.back(); }
  const_reference back() const { return elems.back(); }
  
  /** Returns pointer to the underlying array serving as element storage. The pointer is such that range [data(), data() + size()) is always a vlid rnge, even if the container is empty (data() is not dereferenceable in that case). */
  T* data() noexcept { return elems.data(); }
  const T* data() const noexcept { return elems.data(); }
  
  /** Returns an iterator to the first element of the vector. If the vector is empty, the returned iterator will be equal to end(). */
  iterator begin() noexcept { return elems.begin(); }
  const_iterator begin() const noexcept { return elems.begin(); }
  const_iterator cbegin() const noexcept { return elems.cbegin(); }
  
  /** Returns an iterator to the element following the last element of the vector. This element acts as a placeholder; attempting to access it results in undefined behaviour. */
  iterator end() noexcept { return elems.end(); }
  const_iterator end() const noexcept { return elems.end(); }
  const_iterator cend() const noexcept { return elems.cend(); }
  
  /** Returns a reverse iterator to the first element of the reversed vector. It corresponds to the last element of the non-reversed vector. If the vector is empty, the returned iterator is equal to rend(). */
  reverse_iterator rbegin() noexcept { return elems.rbegin(); }
  const_reverse_iterator rbegin() const noexcept { return elems.rbegin(); }
  const_reverse_iterator crbegin() const noexcept { return elems.crbegin(); }
  
  /** Returns a reverse iterator to the element following the last element of the reversed vector. It corresponds to the element preceding the first element of the non-reversed vector. This element acts as a placeholder, attempting to access it results in undefined behavior. */
  reverse_iterator rend() noexcept { return elems.rend(); }
  const_reverse_iterator rend() const noexcept { return elems.rend(); }
  const_reverse_iterator crend() const noexcept { return elems.crend(); }
  
  /** Returns the number of elements. */
  size_type size() const { elems.size(); }
  /** Returns the minimum index. */
  int64_t min_index() const { return minindex; }
  /** Returns the maximum index. */
  int64_t max_index() const { return maxindex; }
  /** Resize the bounds of the container. */
  void resize(int64_t min, int64_t max) {
    minindex = min;
    maxindex = max;
    elems.resize(maxindex - minindex + 1);
  }
  void resize(int64_t min, int64_t max, const value_type& value) {
    minindex = min;
    maxindex = max;
    elems.resize(maxindex - minindex + 1, value);
  }
  
protected:
  base_type elems;
  int64_t minindex, maxindex;
};

}
