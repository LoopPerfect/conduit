#include "gtest/gtest.h"
#include <conduit/range.hpp>
#include <conduit/find.hpp>

using namespace conduit;

TEST(Seq, findOne) {
  
  auto transform = find([](auto x) { 
    return x == 3; 
  });
  
  auto needle = 0;
  for (auto x : transform(range(0, 4))) {
    needle = x;
  }

  EXPECT_EQ(needle, 3);

}

TEST(Seq, findNone) {
  
  auto needle = 0;
  
  auto transform = find([](auto x) { 
    return x == 10; 
  });
  
  for (auto x : transform(range(0, 4))) {
    needle = x;
  }

  EXPECT_EQ(needle, 0);
}
