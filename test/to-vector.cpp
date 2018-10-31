#include <gtest/gtest.h>
#include <conduit/to-vector.hpp>
#include <conduit/range.hpp>
#include <conduit/filter.hpp>
#include <conduit/take.hpp>
#include <conduit/compose.hpp>

using namespace conduit;
using namespace operators;

TEST(Seq, toVector) {

  auto items = range()
    >> filter([](auto x){ return x%2==0; })
    >> take(4)
    >> toVector();
  
  int i = 0;
  for (auto x : items) {
    EXPECT_EQ(i*2, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
}


