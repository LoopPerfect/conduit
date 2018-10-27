#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/flatmap.hpp>

using namespace conduit;

TEST(Seq, flatMap) {
  auto transform = flatMap([](auto x) -> seq<int> { 
    if (x%2)
      co_yield x;  
  });

  auto i = 0;
  for (auto x : transform(count(0))) {
    EXPECT_EQ(1+i*2, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
