#include "gtest/gtest.h"
#include <conduit/range.hpp>
#include <conduit/foreach.hpp>
#include <conduit/compose.hpp>

using namespace conduit;
using namespace operators;
TEST(Seq, forEach) {
  auto i = 0;
  auto items = range(1, 4)
    >> forEach([&](auto x){i=x;});
  
  for (auto x : items) {
    EXPECT_EQ(i, x);
  }

  EXPECT_EQ(i, 3);
}

