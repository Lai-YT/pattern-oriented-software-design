#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void SetUp() override {
    head_ = new Point{2, -3};
    tail_ = new Point{-3, 2};
    vector_ = new TwoDimensionalVector{head_, tail_};
  }

  void TearDown() override {
    delete vector_;
    delete tail_;
    delete head_;
  }

  TwoDimensionalVector* vector_;

 private:
  Point* head_;
  Point* tail_;
};

TEST_F(TwoDimensionalVectorTest, CheckHeadTailSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), vector_->head());
  EXPECT_EQ(Point(-3, 2), vector_->tail());
}

TEST_F(TwoDimensionalVectorTest, CheckHeadTailAliasSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), *vector_->a());
  EXPECT_EQ(Point(-3, 2), *vector_->b());
}

TEST_F(TwoDimensionalVectorTest, TestInfo) {
  ASSERT_EQ("Vector ((2.00, -3.00), (-3.00, 2.00))", vector_->info());
}

TEST_F(TwoDimensionalVectorTest, TestLength) {
  const auto head = Point{1, -1};
  const auto tail = Point{0, 0};
  const auto vector = TwoDimensionalVector{&head, &tail};

  ASSERT_NEAR(1.414, vector.length(), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProduct) {
  const auto head_1 = Point{0, 0};
  const auto tail_1 = Point{4, 5};
  const auto vector_1 = TwoDimensionalVector{&head_1, &tail_1};
  const auto head_2 = Point{0, 0};
  const auto tail_2 = Point{-3, 2};
  const auto vector_2 = TwoDimensionalVector{&head_2, &tail_2};

  ASSERT_NEAR(23, vector_1.cross(&vector_2), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProductAngleOverPi) {
  const auto head_1 = Point{0, 0};
  const auto tail_1 = Point{4, 5};
  const auto vector_1 = TwoDimensionalVector{&head_1, &tail_1};
  const auto head_2 = Point{0, 0};
  const auto tail_2 = Point{-3, -10};
  const auto vector_2 = TwoDimensionalVector{&head_2, &tail_2};

  ASSERT_NEAR(-25, vector_1.cross(&vector_2), DELTA);
}
