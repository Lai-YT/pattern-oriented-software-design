#include <gtest/gtest.h>

#include "../src/circle.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    circle_ =
        new Circle{new TwoDimensionalVector{new Point{1, 2}, new Point{-3, 5}}};
  }

  void TearDown() override {
    delete circle_;
  }

  Circle* circle_;
};

TEST_F(CircleTest, TestRadius) {
  ASSERT_NEAR(5, circle_->radius(), DELTA);
}

TEST_F(CircleTest, TestArea) {
  ASSERT_NEAR(78.540, circle_->area(), DELTA);
}

TEST_F(CircleTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_->perimeter(), DELTA);
}

TEST_F(CircleTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_->info());
}

class CirclePolymorphismTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    circle_ =
        new Circle{new TwoDimensionalVector{new Point{1, 2}, new Point{-3, 5}}};
  }

  void TearDown() override {
    delete circle_;
  }

  Shape* circle_;
};

TEST_F(CirclePolymorphismTest, TestArea) {
  ASSERT_NEAR(78.540, circle_->area(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_->perimeter(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_->info());
}
