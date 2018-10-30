#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/drop-until.hpp>
#include <conduit/allocators/terminate.hpp>

using namespace conduit;

TEST(Seq, dropUntil) {
  auto i = 4;
  
  auto transform = dropUntil([](auto x) { 
    return x > 3; 
  });
  
  for (auto x : transform(range(0))) {
    EXPECT_EQ(i, x);
    ++i;
    if (i == 8) 
      break;
  }

  EXPECT_EQ(i, 8);
}


