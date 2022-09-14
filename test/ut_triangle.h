#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class TriangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    triangle_ = new Triangle{
        new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
        new TwoDimensionalVector{new Point{3, 4}, new Point{3, 0}}};
  }

  void TearDown() override {
    delete triangle_;
  }

  Triangle* triangle_;
};

TEST_F(TriangleTest, TestPerimeter) {
  ASSERT_NEAR(12, triangle_->perimeter(), DELTA);
}

TEST_F(TriangleTest, TestArea) {
  ASSERT_NEAR(6, triangle_->area(), DELTA);
}

TEST_F(TriangleTest, TestInfo) {
  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      triangle_->info());
}
