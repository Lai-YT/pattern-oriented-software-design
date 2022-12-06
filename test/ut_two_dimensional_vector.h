#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  const TwoDimensionalVector vector_{Point{2, -3}, Point{-3, 2}};
};

TEST_F(TwoDimensionalVectorTest, CheckHeadTailSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), vector_.head());
  EXPECT_EQ(Point(-3, 2), vector_.tail());
}

TEST_F(TwoDimensionalVectorTest, CheckHeadTailAliasSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), *vector_.a());
  EXPECT_EQ(Point(-3, 2), *vector_.b());
}

TEST_F(TwoDimensionalVectorTest, TestInfo) {
  ASSERT_EQ("Vector ((2.00, -3.00), (-3.00, 2.00))", vector_.info());
}

TEST_F(TwoDimensionalVectorTest, TestLength) {
  const auto vector = TwoDimensionalVector{Point{1, -1}, Point{0, 0}};

  ASSERT_NEAR(1.414, vector.length(), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestDot) {
  const auto vector = TwoDimensionalVector{Point{3, -1}, Point{0, 0}};

  ASSERT_NEAR(20, vector.dot(&vector_), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProduct) {
  const auto vector_1 = TwoDimensionalVector{Point{0, 0}, Point{4, 5}};
  const auto vector_2 = TwoDimensionalVector{Point{0, 0}, Point{-3, 2}};

  ASSERT_NEAR(23, vector_1.cross(&vector_2), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProductAngleOverPi) {
  const auto vector_1 = TwoDimensionalVector{Point{0, 0}, Point{4, 5}};
  const auto vector_2 = TwoDimensionalVector{Point{0, 0}, Point{-3, -10}};

  ASSERT_NEAR(-25, vector_1.cross(&vector_2), DELTA);
}

TEST(VectorHelperTest, HasCommonPointWithVector) {
  const auto vector = TwoDimensionalVector{Point{4, 5}, Point{0, 0}};

  ASSERT_TRUE(HasCommonPointWithVector(Point{4, 5}, vector));
}

TEST(VectorHelperTest, HasNoCommonPointWithVector) {
  const auto vector = TwoDimensionalVector{Point{4, 5}, Point{0, 0}};

  ASSERT_FALSE(HasCommonPointWithVector(Point{5, 4}, vector));
}

TEST(VectorHelperTest, FindCommonPointOfVectors) {
  const auto vector_1 = TwoDimensionalVector{Point{4, 5}, Point{0, 0}};
  const auto vector_2 = TwoDimensionalVector{Point{0, 0}, Point{-3, -10}};
  const auto expect_common_point = Point{0, 0};

  const auto actual_common_point =
      *FindCommonPointOfVectors(vector_1, vector_2);

  ASSERT_EQ(expect_common_point, actual_common_point);
}

TEST(VectorHelperTest,
     FindCommonPointOfVectorsShouldReturnNullIfNoCommonPoint) {
  const auto vector_1 = TwoDimensionalVector{Point{1, 2}, Point{-3, -4}};
  const auto vector_2 = TwoDimensionalVector{Point{0, 0}, Point{-3, -10}};

  ASSERT_TRUE(FindCommonPointOfVectors(vector_1, vector_2) == nullptr);
}
