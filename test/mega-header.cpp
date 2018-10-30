#include <gtest/gtest.h>
#include <conduit/conduit.hpp>

using namespace conduit;

TEST(Seq, mega_header) {
  auto i = 0;
  auto elems = just(0, 1, 2);
  for (auto x : elems()) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 3);
}
