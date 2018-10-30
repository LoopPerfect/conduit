#include <gtest/gtest.h>
#include <conduit/range.hpp>
#include <conduit/zip.hpp>
#include <conduit/compose.hpp>

// FIXME: get rid of this allocation
#include <conduit/allocators/counter.hpp>

using namespace conduit;

TEST(Seq, zip) {
  reset_alloc_counter();
  
  auto values = zip(
    [](auto x, auto y) { return x+y; },
    range(0), 
    range(0)
  );
  
  auto i = 0;
  for (auto x : values) {
    EXPECT_EQ(i+i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);  
  EXPECT_EQ(get_alloc_counter(), 2);
}

TEST(Seq, zipWith) {
  reset_alloc_counter();
  
  using namespace operators; 
  auto values = range(0) 
    >> zipWith(factory(range, 0), [](auto x, auto y) { return x+y; })
    >> zipWith(factory(range, 0), [](auto x, auto y) { return x+y; });
 
  auto i = 0;
  for (auto x : values) {
    EXPECT_EQ(i+i+i, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
  EXPECT_EQ(get_alloc_counter(), 4);
}
