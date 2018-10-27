#include "gtest/gtest.h"
#include <conduit/count.hpp>

using namespace conduit;

TEST(Seq, count) {
  auto i = 0;
  for (auto x : count(0)) {
    EXPECT_EQ(i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
