//
// Created by 28150 on 2023/2/28.
//

#ifndef ZTL_SRC_INCLUDE_ALLOCATOR_H
#define ZTL_SRC_INCLUDE_ALLOCATOR_H
#include "ztl_concepts/_allocator.h"
#include <cstdlib>
#include <memory>
namespace ztl {
template <class T>
struct allocator {
  using value_type      = T;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer         = value_type*;
  using const_pointer   = const value_type*;

  constexpr value_type* allocate(size_type n) {
    return static_cast<value_type*>(std::malloc(n * sizeof(T)));
  }
  constexpr void deallocate(value_type* value, size_type n) {
    std::free(value);
  }
  constexpr allocator() {
    static_assert(concepts::IsAllocator<value_type, allocator<value_type>>);
  }
};

template <class A>
struct allocator_traits {
  using allocator_type = A;
  using value_type     = typename allocator_type::value_type;
  using pointer        = typename allocator_type::pointer;
  using size_type      = typename allocator_type::size_type;
  using const_pointer  = typename allocator_type::const_pointer;

  [[nodiscard]] static constexpr pointer allocate(allocator_type& a,
                                                  size_type n) {
    return a.allocate(n);
  }

  static constexpr void deallocate(allocator_type& a, pointer p, size_type n) {
    a.deallocate(p, n);
  }

  template <class... Args>
  static constexpr void construct(allocator_type& a, pointer p,
                                  Args&&... args) {
    std::construct_at(p, std::forward<Args>(args)...);
  }

  static constexpr void destory(allocator_type& a, pointer p) {
    std::destroy_at(p);
  }
};

} // namespace ztl
#endif // ZTL_SRC_INCLUDE_ALLOCATOR_H
