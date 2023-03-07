/**
 * created on 2023/3/7
 * 实现ztl::vector
 */

#ifndef ZTL_SRC_INCLUDE_VECTOR_H
#define ZTL_SRC_INCLUDE_VECTOR_H
#include "allocator.h"
#include "iterator.h"
#include <iterator>
namespace ztl {

template <class T, class Alloc = allocator<T>>
class vector {
public:
  struct Iterator;

  using value_type             = T;
  using allocator_type         = Alloc;
  using size_type              = size_t;
  using difference_type        = ptrdiff_t;
  using reference              = value_type&;
  using const_reference        = const value_type&;
  using pointer                = std::allocator_traits<Alloc>::pointer;
  using const_pointer          = std::allocator_traits<Alloc>::const_pointer;
  using iterator               = value_type*;
  using const_iterator         = const iterator;
  using reverse_iterator       = ztl::reverse_iterator<iterator>;
  using const_reverse_iterator = const reverse_iterator;

  /*
  // 下面是随机访问迭代器需要实现的所有函数
  struct Iterator {
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;
    using iterator_category = std::random_access_iterator_tag;
    // clang-format off
    Iterator() = default;
    // TODO: 实现下面的函数
    reference                    operator*() {}
    reference                    operator*() const {}
    Iterator&                    operator++() {}
    Iterator                     operator++(int) {}
    Iterator&                    operator--() {}
    Iterator                     operator--(int) {}

    Iterator                     operator+(difference_type n) {}
    Iterator                     operator+(const difference_type n) const {}
    friend Iterator              operator+(difference_type n, const Iterator& rhs) {}

    Iterator                     operator-(difference_type n) const {}
    difference_type              operator-(const Iterator& rhs) const {}
    friend Iterator              operator-(difference_type n, const Iterator& rhs) {}

    Iterator&                    operator+=(difference_type n) {}
    Iterator&                    operator-=(difference_type n) {}

    friend bool                  operator==(const Iterator& lhs, const Iterator& rhs) {}
    friend std::partial_ordering operator<=>(const Iterator& lhs,
                                             const Iterator& rhs) {}

    reference                    operator[](const difference_type n) const {}

    pointer ptr;
    // clang-format on
  };
  // 难崩 刚开始没想到指针完美复合随机访问迭代器的特性
   */
};

static_assert(std::random_access_iterator<vector<int>::iterator>);
} // namespace ztl



#endif // ZTL_SRC_INCLUDE_VECTOR_H
