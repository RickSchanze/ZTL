/**
 * Created by 28150 on 2023/3/1.
 * 此文件用于实现迭代器常用算法
 * TODO: 对于基础类型的iterator适配
 */

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

/*
 * 反向迭代器适配器，举个例子
 * 对于正向vector:
 * [    1    2    3    4    5    6    ]
 * 假如目前vector的迭代器在这里
 * [    1    2    3    4    5    6    ]
 *                     ^it
 * 则拿迭代器it来初始化一个反向迭代器的话，它的current会在这里
 * [    1    2    3    4    5    6    ]
 *                     ^current
 * 而反向迭代器实际所指的位置（记为rit）与current的关系，在正向迭代器的角度来看，
 * 其实是*rit = *(current - 1)
 * 即
 * [    1    2    3    4    5    6    ]
 *                ^rit ^current
 */
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
    current_ = std::move(x);
  }
  constexpr reverse_iterator(const reverse_iterator& other)
      : current_(other.base()) {}

  constexpr reverse_iterator& operator=(const reverse_iterator& other) {
    current_ = other.base();
    return *this;
  }

  constexpr iterator_type base() const { return current_; }
  constexpr reference operator*() const {
    auto tmp = current_;
    return *--tmp;
  }
  constexpr pointer operator->() const { return &(operator*()); }

  // 标准双向迭代器约束并未提供[]的约束，因此要使用这个需要本身就有[]操作
  constexpr value_type operator[](difference_type n) const {
    return *(*this + n);
  }
  reverse_iterator& operator++() {
    --current_;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current_;
    return tmp;
  }
  reverse_iterator& operator--() {
    ++current_;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current_;
    return tmp;
  }
  reverse_iterator operator+(difference_type n) const {
    auto temp = current_;
    ztl::advance(temp, -n);
    return reverse_iterator(temp);
  }
  reverse_iterator& operator+=(difference_type n) {
    ztl::advance(current_, -n);
    return *this;
  }
  reverse_iterator operator-(difference_type n) const {
    auto temp = current_;
    ztl::advance(temp, n);
    return reverse_iterator(temp);
  }
  reverse_iterator& operator-=(difference_type n) {
    ztl::advance(current_, n);
    return *this;
  }

  /**
   * 由于暂未理解为什么要把两个iterator_type的类型进行比较，因此
   * 先设为只允许同一类型
   */
  template <class RIter>
  friend std::partial_ordering operator<=>(const reverse_iterator<RIter>& lhs,
                                           const reverse_iterator<RIter>& rhs);

  template <class RIter>
  friend bool operator==(const reverse_iterator<RIter>& lhs,
                         const reverse_iterator<RIter>& rhs);

private:
  // 这是个底层迭代器
  // see https://zh.cppreference.com/w/cpp/iterator/reverse_iterator/base
  iterator_type current_;
};

/**
 * 本来是反向的
 * 再反向一次成正向的了
 * 因此使用rhs <=> lhs
 * @tparam RIter
 * @param lhs
 * @param rhs
 * @return
 */
template <class RIter>
std::partial_ordering operator<=>(const reverse_iterator<RIter>& lhs,
                                  const reverse_iterator<RIter>& rhs) {
  return rhs.current_ <=> lhs.current_;
}

template <class RIter>
bool operator==(const reverse_iterator<RIter>& lhs,
                const reverse_iterator<RIter>& rhs) {
  return rhs.current_ == lhs.current_;
}
} // namespace ztl
#endif // ZTL_SRC_INCLUDE_ITERATOR_H
