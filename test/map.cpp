#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/map.hpp>

using namespace conduit;

TEST(Seq, map) {
  auto i = 0;
  auto transform = map([](auto x) { return x * x; });
  for (auto x : transform(count(0))) {
    EXPECT_EQ(i * i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
