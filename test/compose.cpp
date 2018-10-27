#include "gtest/gtest.h"
#include <conduit/compose.hpp>
#include <conduit/count.hpp>
#include <conduit/map.hpp>

using namespace conduit;

TEST(Seq, compose) {
  auto i = 0;

  auto transform =
    compose(map([](auto x) { return x + 1; }),
            map([](auto x) { return x + 1; }),
            map([](auto x) { return x + 1; }));

  for (auto x : transform(count(0))) {
    EXPECT_EQ(i + 3, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}

TEST(Seq, composeTree) {
  auto i = 0;

  auto T1 = compose(map([](auto x) { return x + 1; }),
                    map([](auto x) { return x + 1; }),
                    map([](auto x) { return x + 1; }));

  auto T2 = compose(T1, T1);

  auto transform = compose(T2, T2);

  for (auto x : transform(count(0))) {
    EXPECT_EQ(i + 12, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}

TEST(Seq, operators) {
  using namespace operators;
  auto i = 0;

  auto values = count(0) >>
                map([](auto x) { return x + 1; }) >>
                map([](auto x) { return x + 1; }) >>
                map([](auto x) { return x + 1; });

  for (auto x : values) {
    EXPECT_EQ(i + 3, x);
    if (i > 3)
      break;
    ++i;
  }

  EXPECT_EQ(i, 4);
}
