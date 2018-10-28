#include "gtest/gtest.h"
#include <conduit/count.hpp>
#include <conduit/zip.hpp>
#include <conduit/compose.hpp>

using namespace conduit;

TEST(Seq, zip) {
  
  auto values = zip([](auto x, auto y) { return x+y; },
      count(0), count(0));
  
  auto i = 0;
  for (auto x : values) {
    EXPECT_EQ(i+i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}

TEST(Seq, zipWith) {
  using namespace operators; 
  auto values = count(0) 
    >> zipWith(factory(count, 0), [](auto x, auto y) { return x+y; })
    >> zipWith(factory(count, 0), [](auto x, auto y) { return x+y; });
 
  auto i = 0;
  for (auto x : values) {
    EXPECT_EQ(i+i+i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
