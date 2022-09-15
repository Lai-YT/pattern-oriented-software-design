#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

class RectangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  RectangleTest() {
    underlaying_vector_1_ = new TwoDimensionalVector(
        underlaying_vector_head_1_, underlaying_vector_tail_1_);
    underlaying_vector_2_ = new TwoDimensionalVector(
        underlaying_vector_head_2_, underlaying_vector_tail_2_);
    rectangle_ = new Rectangle{underlaying_vector_1_, underlaying_vector_2_};
  }

  ~RectangleTest() {
    delete rectangle_;
    delete underlaying_vector_1_;
    delete underlaying_vector_tail_1_;
    delete underlaying_vector_head_1_;
    delete underlaying_vector_2_;
    delete underlaying_vector_tail_2_;
    delete underlaying_vector_head_2_;
  }

  Rectangle* rectangle_;

 private:
  const Point* underlaying_vector_head_1_ = new Point{0, 0};
  const Point* underlaying_vector_tail_1_ = new Point{3, 0};
  const TwoDimensionalVector* underlaying_vector_1_;
  const Point* underlaying_vector_head_2_ = new Point{0, 0};
  const Point* underlaying_vector_tail_2_ = new Point{0, 4};
  const TwoDimensionalVector* underlaying_vector_2_;
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
  const auto underlaying_vector_head_1 = Point{0, 0};
  const auto underlaying_vector_tail_1 = Point{3, 1};
  const auto underlaying_vector_1 = TwoDimensionalVector{
      &underlaying_vector_head_1, &underlaying_vector_tail_1};
  const auto underlaying_vector_head_2 = Point{0, 0};
  const auto underlaying_vector_tail_2 = Point{0, 4};
  const auto underlaying_vector_2 = TwoDimensionalVector{
      &underlaying_vector_head_2, &underlaying_vector_tail_2};

  ASSERT_THROW(
      {
        const auto rectangle =
            Rectangle(&underlaying_vector_1, &underlaying_vector_2);
      },
      Rectangle::NonOrthogonalSideException);
}

TEST_F(RectangleTest, PassingSidesWithNoCommonPointShouldThrowException) {
  const auto underlaying_vector_head_1 = Point{1, 0};
  const auto underlaying_vector_tail_1 = Point{3, 0};
  const auto underlaying_vector_1 = TwoDimensionalVector{
      &underlaying_vector_head_1, &underlaying_vector_tail_1};
  const auto underlaying_vector_head_2 = Point{0, 0};
  const auto underlaying_vector_tail_2 = Point{0, 4};
  const auto underlaying_vector_2 = TwoDimensionalVector{
      &underlaying_vector_head_2, &underlaying_vector_tail_2};

  ASSERT_THROW(
      {
        const auto rectangle =
            Rectangle(&underlaying_vector_1, &underlaying_vector_2);
      },
      Rectangle::NoCommonPointException);
}

class RectanglePolymorphismTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  RectanglePolymorphismTest() {
    underlaying_vector_1_ = new TwoDimensionalVector(
        underlaying_vector_head_1_, underlaying_vector_tail_1_);
    underlaying_vector_2_ = new TwoDimensionalVector(
        underlaying_vector_head_2_, underlaying_vector_tail_2_);
    rectangle_ = new Rectangle{underlaying_vector_1_, underlaying_vector_2_};
  }

  ~RectanglePolymorphismTest() {
    delete rectangle_;
    delete underlaying_vector_1_;
    delete underlaying_vector_tail_1_;
    delete underlaying_vector_head_1_;
    delete underlaying_vector_2_;
    delete underlaying_vector_tail_2_;
    delete underlaying_vector_head_2_;
  }

  Shape* rectangle_;

 private:
  const Point* underlaying_vector_head_1_ = new Point{0, 0};
  const Point* underlaying_vector_tail_1_ = new Point{3, 0};
  const TwoDimensionalVector* underlaying_vector_1_;
  const Point* underlaying_vector_head_2_ = new Point{0, 0};
  const Point* underlaying_vector_tail_2_ = new Point{0, 4};
  const TwoDimensionalVector* underlaying_vector_2_;
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
