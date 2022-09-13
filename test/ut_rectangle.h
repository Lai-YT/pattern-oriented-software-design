#include <gtest/gtest.h>

#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

TEST(RectangleTest, TestInfo) {
  const auto rectangle = Rectangle{TwoDimensionalVector{{-2, 1}, {1.5, 0.47}},
                                   TwoDimensionalVector{{-2, 1}, {-1.47, 4.5}}};

  ASSERT_EQ(
      "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))",
      rectangle.info());
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
