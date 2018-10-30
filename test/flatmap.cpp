#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/flatmap.hpp>

// FIXME: get rid of this allocation
#include <conduit/allocators/counter.hpp>

using namespace conduit;

TEST(Seq, flatMap) {
  reset_alloc_counter();
  
  auto transform = flatMap([](auto x) -> seq<int> { 
    if (x%2)
      co_yield x;  
  });

  auto i = 0;
  for (auto x : transform(range(0, 8))) {
    EXPECT_EQ(1+i*2, x);
    ++i;
  }

  EXPECT_EQ(i, 4);
  EXPECT_EQ(get_alloc_counter(), 9);
}
