#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/find.hpp>

using namespace conduit;

auto haystack = []() -> seq<int> {
  co_yield 1;
  co_yield 2;
  co_yield 3;
  co_yield 4;
};

TEST(Seq, findOne) {
  
  auto transform = find([](auto x) { 
    return x == 3; 
  });
  
  auto needle = 0;
  for (auto x : transform(haystack())) {
    needle = x;
  }

  EXPECT_EQ(needle, 3);

}

TEST(Seq, findNone) {
  
  auto needle = 0;
  
  auto transform = find([](auto x) { 
    return x == 10; 
  });
  
  for (auto x : transform(haystack())) {
    needle = x;
  }

  EXPECT_EQ(needle, 0);
}
