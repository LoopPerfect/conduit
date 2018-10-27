#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/take-while.hpp>

using namespace conduit;

TEST(Seq, takeWhile) {
  auto i = 0;
  
  auto transform = takeWhile([](auto x) { 
    return x < 4; 
  });
  
  for (auto x: transform(count(0))) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
}
