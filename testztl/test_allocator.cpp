//
// Created by 28150 on 2023/2/28.
//
#include "allocator.h"
#include "gtest/gtest.h"

TEST(TestAllocator, Test1) {
  ztl::Allocator<int> alloc;
  constexpr ztl::AllocatorTraits<ztl::Allocator<int>> traits;
  auto p = traits.allocate(alloc, 10);
  for (int i = 0; i < 10; ++i) {
    traits.construct(alloc, p + i, i);
    EXPECT_EQ(i, p[i]);
  }
  traits.deallocate(alloc, p, 10);
  EXPECT_NE(*p, 1);
}