#include "gtest/gtest.h"
#include <conduit/compose.hpp>
#include <conduit/starts-with.hpp>
#include <conduit/ends-with.hpp>

using namespace conduit;

namespace {
auto seq1() -> seq<int> {
  co_yield 1;
  co_yield 2;
  co_yield 3;
}

auto seq2() -> seq<int> {
  co_yield 4;
  co_yield 5;
  co_yield 6;
}


auto seq3() -> seq<int> {
  co_yield 7;
  co_yield 8;
  co_yield 9;
}
}

TEST(Seq, concat) {
  using namespace operators;

  auto items = seq2()
    >> startsWith(seq1())
    >> endsWith(seq3());
  
  int i = 1;
  for(auto x: items) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 10);

}


TEST(Seq, concat2) {
  using namespace operators;

  auto items = seq2()
    >> endsWith(seq3())
    >> startsWith(seq1());
  
  int i = 1;
  for(auto x: items) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 10);

}

