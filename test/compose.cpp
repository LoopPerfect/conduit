#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/map.hpp>
#include <conduit/compose.hpp>

using namespace conduit;

TEST(Seq, compose) {
  auto i = 0;
 
  auto transform = compose(
    map([](auto x){ return x + 1; }), 
    map([](auto x){ return x + 1; }), 
    map([](auto x){ return x + 1; }) 
  );
  
  for (auto x : transform(count(0))) {
    EXPECT_EQ(i+3, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
