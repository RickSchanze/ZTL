//
// Created by 28150 on 2023/2/28.
//

#ifndef ZTL_SRC_INCLUDE_CONCEPTS_ALLOCATOR_H
#define ZTL_SRC_INCLUDE_CONCEPTS_ALLOCATOR_H
#include <utility>
namespace ztl::concepts {
// clang-format off
template <class V, class T>
concept IsAllocator = requires(V* value, T allocator, std::size_t n) {
  typename T::value_type;
  typename T::size_type;
  typename T::difference_type;

  {allocator.allocate(n)} -> std::same_as<V*>;
  {allocator.deallocate(value, n)} -> std::same_as<void>;

  {T()};
};
}
#endif // ZTL_SRC_INCLUDE_CONCEPTS_ALLOCATOR_H
