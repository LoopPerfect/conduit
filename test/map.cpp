#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/map.hpp>

using namespace conduit;

TEST(Seq, map) {
  auto i = 0;
  auto transform = map([](auto x) { return x * x; });
  for (auto x : transform(range(0, 4))) {
    EXPECT_EQ(i * i, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
}
