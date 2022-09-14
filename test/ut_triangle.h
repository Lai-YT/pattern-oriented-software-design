#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

TEST(TriangleTest, TestPerimeter) {
  const auto tri =
      Triangle{new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
               new TwoDimensionalVector{new Point{3, 4}, new Point{3, 0}}};

  ASSERT_NEAR(12, tri.perimeter(), 0.001);
}

TEST(TriangleTest, TestArea) {
  const auto tri =
      Triangle{new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
               new TwoDimensionalVector{new Point{3, 4}, new Point{3, 0}}};

  ASSERT_NEAR(6, tri.area(), 0.001);
}

TEST(TriangleTest, TestInfo) {
  const auto tri =
      Triangle{new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
               new TwoDimensionalVector{new Point{3, 4}, new Point{3, 0}}};

  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      tri.info());
}
