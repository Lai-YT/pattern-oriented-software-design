#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

class RectangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    rectangle_ = new Rectangle{
        new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
        new TwoDimensionalVector{new Point{0, 0}, new Point{0, 4}}};
  }

  void TearDown() override {
    delete rectangle_;
  }

  Rectangle* rectangle_;
};

TEST_F(RectangleTest, TestLength) {
  ASSERT_NEAR(3, rectangle_->length(), DELTA);
}

TEST_F(RectangleTest, TestWidth) {
  ASSERT_NEAR(4, rectangle_->width(), DELTA);
}

TEST_F(RectangleTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_->info());
}

TEST_F(RectangleTest, TestArea) {
  ASSERT_NEAR(12, rectangle_->area(), DELTA);
}

TEST_F(RectangleTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_->perimeter(), DELTA);
}

TEST_F(RectangleTest, PassingNonOrthognalSidesShouldThrowException) {
  ASSERT_THROW(
      {
        const auto rectangle = Rectangle(
            new TwoDimensionalVector{new Point{0, 0}, new Point{3, 1}},
            new TwoDimensionalVector{new Point{0, 0}, new Point{0, 4}});
      },
      Rectangle::NonOrthogonalSideException);
}

TEST_F(RectangleTest, PassingSidesWithNoCommonPointShouldThrowException) {
  ASSERT_THROW(
      {
        const auto rectangle = Rectangle(
            new TwoDimensionalVector{new Point{1, 0}, new Point{3, 0}},
            new TwoDimensionalVector{new Point{0, 0}, new Point{0, 4}});
      },
      Rectangle::NoCommonPointException);
}

class RectanglePolymorphismTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    rectangle_ = new Rectangle{
        new TwoDimensionalVector{new Point{0, 0}, new Point{3, 0}},
        new TwoDimensionalVector{new Point{0, 0}, new Point{0, 4}}};
  }

  void TearDown() override {
    delete rectangle_;
  }

  Shape* rectangle_;
};

TEST_F(RectanglePolymorphismTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_->info());
}

TEST_F(RectanglePolymorphismTest, TestArea) {
  ASSERT_NEAR(12, rectangle_->area(), DELTA);
}

TEST_F(RectanglePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_->perimeter(), DELTA);
}
