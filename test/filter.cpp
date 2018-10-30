#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/filter.hpp>
#include <conduit/allocators/terminate.hpp>

using namespace conduit;

TEST(Seq, filter) {
  auto i = 4;
  
  auto transform = filter([](auto x) { 
    return x > 3; 
  });
  
  for (auto x : transform(range(0, 8))) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 8);
}
