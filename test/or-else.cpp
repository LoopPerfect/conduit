#include <gtest/gtest.h>
#include <conduit/or-else.hpp>
#include <conduit/range.hpp>
#include <conduit/map.hpp>
#include <conduit/compose.hpp>

#if FIXME_MAKE_FLATMAP_ZERO_COST
#include <conduit/allocators/terminate.hpp>
#endif

using namespace conduit;
using namespace operators;

TEST(Seq, some_or_else) {
  auto i = 0;
  auto alt = factory(range, 0, 2);
  auto items = evaluate(
    range(0, 2),
    orElse(alt)
  );

  for (auto x : items) {
    EXPECT_EQ(i, x);
    ++i;
  }

  EXPECT_EQ(i, 2);
}


TEST(Seq, none_or_else) {
  auto i = 0;
  auto alt = factory(range, 2, 4);
  auto items = evaluate(
    range(0,0),
    orElse(alt)
  );

  for (auto x : items) {
    EXPECT_EQ(i+2, x);
    ++i;
  }

  EXPECT_EQ(i, 2);
}

