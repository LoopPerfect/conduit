#include "gtest/gtest.h"
#include <conduit/range.hpp>
#include <conduit/count.hpp>

using namespace conduit;

TEST(Seq, count_some) {
  auto transform = count(0);
  auto i = 0;
  for (auto x : transform(range(10, 14))) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
}


TEST(Seq, count_none) {
  auto transform = count(0);
  auto i = 0;
  for (auto x : transform(range(0, 0))) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 0);
}
