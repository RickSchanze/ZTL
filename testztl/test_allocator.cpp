//
// Created by 28150 on 2023/2/28.
//
#include "allocator.h"
#include "gtest/gtest.h"
#include <vector>

TEST(TestAllocator, TestFreeUsage) {
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

TEST(TestAllocator, TestStdVector) {
  std::vector<int, ztl::Allocator<int>> vec;
  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(vec[i], i);
  }
}