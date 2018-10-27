#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/filter.hpp>

using namespace conduit;

TEST(Seq, filter) {
  auto i = 4;
  
  auto transform = filter([](auto x) { 
    return x > 3; 
  });
  
  for (auto x : transform(count(0))) {
    EXPECT_EQ(i, x);
    if (i > 7)
      break;
    ++i;
  }

  EXPECT_EQ(i, 8);
}
