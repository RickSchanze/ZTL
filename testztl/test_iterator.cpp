//
// Created by 28150 on 2023/3/1.
//
#include "iterator.h"
#include "gtest/gtest.h"
#include <list>
#include <vector>

TEST(TestIterator, TestAdvance) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  auto iter = vec.begin();
  ztl::advance(iter, 3);
  EXPECT_EQ(*iter, 4);
  ztl::advance(iter, -2);
  EXPECT_EQ(*iter, 2);
}

TEST(TestIterator, TestDistanceRandomAccess) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  auto iter1 = vec.begin(), iter2 = vec.end();
  EXPECT_EQ(ztl::distance(iter1, iter2), 6);
  EXPECT_EQ(ztl::distance(iter2, iter1), -6);
}

TEST(TestIterator, TestDistanceNotRandom) {
  std::list list{1, 2, 3, 4, 5, 6};
  auto iter1 = list.begin(), iter2 = list.end();
  EXPECT_EQ(ztl::distance(iter1, iter2), 6);
}

TEST(TestIterator, TestNext) {
  std::list<int> list{1, 2, 3, 4, 5, 6};
  auto iter = list.begin();
  iter      = ztl::next(iter, 3);
  EXPECT_EQ(*iter, 4);
  iter = ztl::next(iter, -2);
  EXPECT_EQ(*iter, 2);
}

TEST(TestIterator, TestPrev) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  auto iter = vec.end();
  iter      = ztl::prev(iter);
  EXPECT_EQ(*iter, 6);
  iter = ztl::prev(iter, 2);
  EXPECT_EQ(*iter, 4);
  iter = ztl::prev(iter, -1);
  EXPECT_EQ(*iter, 5);
}

TEST(TestReverseIterator, TestCreate) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  auto iter = vec.end() - 1;
  ztl::reverse_iterator rit{iter};
  EXPECT_EQ(*rit, 5);
  iter -= 2;
  ztl::reverse_iterator rit2{iter};
  EXPECT_EQ(*rit2, 3);
  ztl::reverse_iterator rit3{rit2};
  EXPECT_EQ(*rit3, 3);
}

TEST(TestReverseIterator, TestMathOperation) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  auto iter = vec.end();
  ztl::reverse_iterator rit1{iter};
  auto rit2 = rit1 + 2;
  EXPECT_EQ(*rit2, 4);
  EXPECT_EQ(*rit1, 6);
  rit1 += 2;
  EXPECT_EQ(*rit1, 4);
  ztl::reverse_iterator rit3{vec.begin() + 1};
  EXPECT_EQ(*rit3, 1);
  auto rit4 = rit3 - 3;
  EXPECT_EQ(*rit4, 4);
  rit3 -= 3;
  EXPECT_EQ(*rit3, 4);
  rit1--;
  EXPECT_EQ(*rit1, 5);
  rit1++;
  EXPECT_EQ(*rit1, 4);
  rit3++;
  EXPECT_EQ(*rit3, 3);
  rit3--;
  EXPECT_EQ(*rit3, 4);
}

TEST(TestReverseIterator, TestLogicOperation) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  auto iter = vec.end();
  ztl::reverse_iterator rit1{iter};
  ztl::reverse_iterator rit2{iter};
  EXPECT_TRUE(rit1 == rit2);
  EXPECT_FALSE(rit1 != rit2);
  EXPECT_FALSE(rit1 < rit2);
  EXPECT_TRUE(rit1 <= rit2);
  EXPECT_FALSE(rit1 > rit2);
  EXPECT_TRUE(rit1 >= rit2);
  rit2++;
  EXPECT_FALSE(rit1 == rit2);
  EXPECT_TRUE(rit1 != rit2);
  EXPECT_TRUE(rit1 < rit2);
  EXPECT_TRUE(rit1 <= rit2);
  EXPECT_FALSE(rit1 > rit2);
  EXPECT_FALSE(rit1 >= rit2);
  rit1 = ztl::reverse_iterator{iter};
  rit2 = ztl::reverse_iterator{iter};
  rit1++;
  EXPECT_FALSE(rit1 == rit2);
  EXPECT_TRUE(rit1 != rit2);
  EXPECT_FALSE(rit1 < rit2);
  EXPECT_FALSE(rit1 <= rit2);
  EXPECT_TRUE(rit1 > rit2);
  EXPECT_TRUE(rit1 >= rit2);
}
