#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;
};

TEST_F(TwoDimensionalVectorTest, CheckHeadTailSetProperlyByConstructor) {
  const auto vector = TwoDimensionalVector{new Point{2, -3}, new Point{-3, 2}};

  EXPECT_EQ(Point(2, -3), vector.head());
  EXPECT_EQ(Point(-3, 2), vector.tail());
}

TEST_F(TwoDimensionalVectorTest, CheckHeadTailAliasSetProperlyByConstructor) {
  const auto vector = TwoDimensionalVector{new Point{2, -3}, new Point{-3, 2}};

  EXPECT_EQ(Point(2, -3), *vector.a());
  EXPECT_EQ(Point(-3, 2), *vector.b());
}

TEST_F(TwoDimensionalVectorTest, TestInfo) {
  const auto vector = TwoDimensionalVector{new Point{2, -3}, new Point{-3, 2}};

  ASSERT_EQ("Vector ((2.00, -3.00), (-3.00, 2.00))", vector.info());
}

TEST_F(TwoDimensionalVectorTest, TestLength) {
  const auto vector = TwoDimensionalVector{new Point{1, -1}, new Point{0, 0}};

  ASSERT_NEAR(1.414, vector.length(), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProduct) {
  const auto vector_1 = TwoDimensionalVector{new Point{0, 0}, new Point{4, 5}};
  const auto vector_2 = TwoDimensionalVector{new Point{0, 0}, new Point{-3, 2}};

  ASSERT_NEAR(23, vector_1.cross(&vector_2), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProductAngleOverPi) {
  const auto vector_1 = TwoDimensionalVector{new Point{0, 0}, new Point{4, 5}};
  const auto vector_2 =
      TwoDimensionalVector{new Point{0, 0}, new Point{-3, -10}};

  ASSERT_NEAR(-25, vector_1.cross(&vector_2), DELTA);
}
