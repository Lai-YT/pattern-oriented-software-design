#include <gtest/gtest.h>

#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

TEST(RectangleTest, TestLength) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{0, 0}, {3, 0}},
                                   TwoDimensionalVector{{0, 0}, {0, 4}}};
  ASSERT_NEAR(3, rectangle.length(), 0.001);
}

TEST(RectangleTest, TestWidth) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{0, 0}, {3, 0}},
                                   TwoDimensionalVector{{0, 0}, {0, 4}}};
  ASSERT_NEAR(4, rectangle.width(), 0.001);
}

TEST(RectangleTest, TestInfo) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{-2, 1}, {1.5, 0.47}},
                                   TwoDimensionalVector{{-2, 1}, {-1.47, 4.5}}};

  /* clang-format off */
  ASSERT_EQ(
      "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))",
      rectangle.info());
  /* clang-format on */
}

TEST(RectangleTest, TestArea) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{0, 0}, {3, 0}},
                                   TwoDimensionalVector{{0, 0}, {0, 4}}};

  ASSERT_NEAR(12, rectangle.area(), 0.001);
}

TEST(RectangleTest, TestPerimeter) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{0, 0}, {3, 0}},
                                   TwoDimensionalVector{{0, 0}, {0, 4}}};

  ASSERT_NEAR(14, rectangle.perimeter(), 0.001);
}
