#include "gtest/gtest.h"
#include <conduit/just.hpp>

using namespace conduit;

TEST(Seq, just_some) {
  auto i = 0;
  auto elems = just(0, 1, 2);
  for (auto x : elems()) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 3);
}


TEST(Seq, just_none) {
  auto i = 0;
  auto elems = just();
  for (auto x : elems()) {
    (void)x;
    ++i;
  }

  EXPECT_EQ(i, 0);
}

