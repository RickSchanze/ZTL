//
// Created by 28150 on 2023/3/1.
//

// 此文件用于实现迭代器常用算法

#ifndef ZTL_SRC_INCLUDE_ITERATOR_H
#define ZTL_SRC_INCLUDE_ITERATOR_H
#include <iterator> // 仅使用迭代器约束
/*测试用*/
#include "allocator.h"
#include "vector"
/******/
namespace ztl {
/**
 * 把迭代器往前移动n个单位
 * @tparam Iter 输入类型
 * @tparam Distance
 * @param iter
 * @param n
 * @return
 */
template <class Iter, class Distance>
constexpr void advance(Iter& iter, Distance n) {
  using categroy = typename std::iterator_traits<Iter>::iterator_category;
  static_assert(std::is_base_of_v<std::input_iterator_tag, categroy>);

  auto dist = typename std::iterator_traits<Iter>::difference_type(n);
  // 随机访问迭代器直接加
  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, categroy>) {
    iter += dist;
  } else { // 不然就一个一个加
    while (dist > 0) {
      --dist;
      ++iter;
    }
    // dist为负的情况
    if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag,
                                    categroy>) {
      while (dist < 0) {
        ++dist;
        --iter;
      }
    }
  }
};

/**
 * 计算两个迭代器之间的距离，注意输入需要是值类型
 * 注意标准规定的：
 * 如果从first没办法自增加到last
 * 则行为未定义
 * @tparam Iter 迭代器类型
 * @param first
 * @param last
 * @return
 */
template <class Iter>
constexpr typename std::iterator_traits<Iter>::difference_type
distance(Iter first, Iter last) {
  using categroy = typename std::iterator_traits<Iter>::iterator_category;
  // 需要是输入迭代器
  static_assert(std::is_base_of_v<std::input_iterator_tag, categroy>);

  // 随机访问迭代器直接减
  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, categroy>) {
    return last - first;
  } else { // 不然就一个一个减
    typename std::iterator_traits<Iter>::difference_type result = 0;
    while (first != last) {
      ++result;
      ++first;
    }
    return result;
  }
};

/**
 * 迭代器自增
 * @tparam Iter 输入迭代器类型
 * @param it 迭代器
 * @param n 默认为1
 * @return
 */
template <class Iter>
constexpr Iter
next(Iter it, typename std::iterator_traits<Iter>::difference_type n = 1) {
  ztl::advance(it, n);
  return it;
}

/**
 * 迭代器自减
 * @tparam Iter 输入迭代器类型
 * @param it
 * @param n
 * @return
 */
template <class Iter>
constexpr Iter
prev(Iter it, typename std::iterator_traits<Iter>::difference_type n = 1) {
  ztl::advance(it, -n);
  return it;
}

template <class Iter>
class reverse_iterator {
  static_assert(std::bidirectional_iterator<Iter>);

public:
  using iterator_category =
      typename std::iterator_traits<Iter>::iterator_category;
  using iterator_type   = Iter;
  using value_type      = typename std::iterator_traits<Iter>::value_type;
  using difference_type = typename std::iterator_traits<Iter>::difference_type;
  using pointer         = typename std::iterator_traits<Iter>::pointer;
  using reference       = typename std::iterator_traits<Iter>::reference;
  constexpr reverse_iterator() = default;
  constexpr explicit reverse_iterator(iterator_type x) {
    current = std::move(x);
  }
  constexpr reverse_iterator(const reverse_iterator& other)
      : current(other.base()) {}

  constexpr reverse_iterator& operator=(const reverse_iterator& other) {
    current = other.base();
    return *this;
  }

  // TODO: 各种reverse_iterator适配器的方法实现
  constexpr iterator_type base() const { return current; }

private:
  iterator_type current;
};

reverse_iterator<std::vector<int, ztl::allocator<int>>::iterator> a{};
} // namespace ztl
#endif // ZTL_SRC_INCLUDE_ITERATOR_H
