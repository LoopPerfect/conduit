#include <gtest/gtest.h>
#include <conduit/sum.hpp>
#include <conduit/range.hpp>
#include <conduit/compose.hpp>
#include <conduit/map.hpp>

#include <conduit/allocators/terminate.hpp>

using namespace conduit;
using namespace operators;

TEST(Seq, sum_some) {
  auto value = range(0, 4)
    >> sum();
  
  EXPECT_EQ(value, 6);
}


TEST(Seq, sum_none) {
  auto value = range(0, 0)
    >> sum();
  
  EXPECT_EQ(value, 0);
}


TEST(Seq, sum_floats) {
  auto value = range(0, 4)
    >> map([](auto x) { return (float)x; })
    >> sum();

  EXPECT_EQ(value, 6.0f);
}
