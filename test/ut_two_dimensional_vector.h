#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

TEST(TwoDimensionalVectorTest, CheckHeadTailSetProperlyByConstructor) {
  const auto vector = TwoDimensionalVector{{2, -3}, {-3, 2}};

  EXPECT_EQ(Point(2, -3), vector.head());
  EXPECT_EQ(Point(-3, 2), vector.tail());
}

TEST(TwoDimensionalVectorTest, TestInfo) {
  const auto vector = TwoDimensionalVector{{2, -3}, {-3, 2}};

  ASSERT_EQ("Vector ((2.00, -3.00), (-3.00, 2.00))", vector.info());
}

TEST(TwoDimensionalVectorTest, TestLength) {
  const auto vector = TwoDimensionalVector{{1, -1}, {0, 0}};

  ASSERT_NEAR(1.414, vector.length(), 0.001);
}

TEST(TwoDimensionalVectorTest, TestDotProduct) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 5}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, 2}};

  ASSERT_EQ(-2, vector_1.dot(vector_2));
}

TEST(TwoDimensionalVector, TestCrossProduct) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 5}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, 2}};

  ASSERT_NEAR(23, vector_1.cross(vector_2), 0.001);
}

TEST(TwoDimensionalVector, TestCrossProductAngleOverPi) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 5}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, -10}};

  ASSERT_NEAR(-25, vector_1.cross(vector_2), 0.001);
}
