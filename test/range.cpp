#include <gtest/gtest.h>
#include <conduit/range.hpp>

#include <conduit/allocators/terminate.hpp>

using namespace conduit;

TEST(Seq, range) {
  auto i = 0;
  for (auto x : range(0, 4)) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
}
