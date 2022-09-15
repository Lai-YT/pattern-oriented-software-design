#include <gtest/gtest.h>

#include "../src/circle.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    underlaying_vector_head_ = new Point{1, 2};
    underlaying_vector_tail_ = new Point{-3, 5};
    underlaying_vector_ = new TwoDimensionalVector{underlaying_vector_head_,
                                                   underlaying_vector_tail_};
    circle_ = new Circle{underlaying_vector_};
  }

  void TearDown() override {
    delete circle_;
    delete underlaying_vector_;
    delete underlaying_vector_tail_;
    delete underlaying_vector_head_;
  }

  Circle* circle_;

 private:
  TwoDimensionalVector* underlaying_vector_;
  Point* underlaying_vector_head_;
  Point* underlaying_vector_tail_;
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
    underlaying_vector_head_ = new Point{1, 2};
    underlaying_vector_tail_ = new Point{-3, 5};
    underlaying_vector_ = new TwoDimensionalVector{underlaying_vector_head_,
                                                   underlaying_vector_tail_};
    circle_ = new Circle{underlaying_vector_};
  }

  void TearDown() override {
    delete circle_;
    delete underlaying_vector_;
    delete underlaying_vector_tail_;
    delete underlaying_vector_head_;
  }

  Shape* circle_;

 private:
  TwoDimensionalVector* underlaying_vector_;
  Point* underlaying_vector_head_;
  Point* underlaying_vector_tail_;
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
