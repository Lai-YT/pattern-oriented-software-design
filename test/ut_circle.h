#include <gtest/gtest.h>

#include "../src/circle.h"

TEST(CircleTest, TestArea) {
  const auto circle = Circle{{{1, 2}, {-3, 5}}};

  ASSERT_NEAR(78.540, circle.area(), 0.001);
}

TEST(CircleTest, TestPerimeter) {
  const auto circle = Circle{{{1, 2}, {-3, 5}}};

  ASSERT_NEAR(31.416, circle.perimeter(), 0.001);
}
