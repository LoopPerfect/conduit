#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/scan.hpp>

#include <conduit/allocators/terminate.hpp>

using namespace conduit;

TEST(Seq, scan) {
  auto sum = scan(0, [](auto a, auto b) { 
    return a + b; 
  });

  auto i = 0;
  auto total = 0;
  for (auto x : sum(range(1, 4))) {
    EXPECT_EQ(total, x);
    ++i;
    total += i;
  }

  EXPECT_EQ(i, 4);
}

TEST(Seq, scan_empty_list) {
  auto sum = scan(0, [](auto a, auto b) { 
    return a + b; 
  });

  auto empty = []() -> seq<int> {
    co_return;
  };

  auto i = 0;
  for (auto x : sum(empty())) {
    EXPECT_EQ(0, x);
    ++i;
  }

  EXPECT_EQ(i, 1);
}
