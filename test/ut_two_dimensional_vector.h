#include <gtest/gtest.h>

#include <optional>

#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  const TwoDimensionalVector vector_{{2, -3}, {-3, 2}};
};

TEST_F(TwoDimensionalVectorTest, CheckHeadTailSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), vector_.head());
  EXPECT_EQ(Point(-3, 2), vector_.tail());
}

TEST_F(TwoDimensionalVectorTest, CheckHeadTailAliasSetProperlyByConstructor) {
  EXPECT_EQ(Point(2, -3), vector_.a());
  EXPECT_EQ(Point(-3, 2), vector_.b());
}

TEST_F(TwoDimensionalVectorTest, TestInfo) {
  ASSERT_EQ("Vector ((2.00, -3.00), (-3.00, 2.00))", vector_.info());
}

TEST_F(TwoDimensionalVectorTest, TestLength) {
  const auto vector = TwoDimensionalVector{{1, -1}, {0, 0}};

  ASSERT_NEAR(1.414, vector.length(), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestDot) {
  const auto vector = TwoDimensionalVector{{3, -1}, {0, 0}};

  ASSERT_NEAR(20, vector.dot(&vector_), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProduct) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 5}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, 2}};

  ASSERT_NEAR(23, vector_1.cross(&vector_2), DELTA);
}

TEST_F(TwoDimensionalVectorTest, TestCrossProductAngleOverPi) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 5}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, -10}};

  ASSERT_NEAR(-25, vector_1.cross(&vector_2), DELTA);
}

TEST(VectorHelperTest, HasCommonPointWithVector) {
  const auto vector = TwoDimensionalVector{{4, 5}, {0, 0}};

  ASSERT_TRUE(HasCommonPointWithVector({4, 5}, vector));
}

TEST(VectorHelperTest, HasNoCommonPointWithVector) {
  const auto vector = TwoDimensionalVector{{4, 5}, {0, 0}};

  ASSERT_FALSE(HasCommonPointWithVector({5, 4}, vector));
}

TEST(VectorHelperTest, FindCommonPointOfVectors) {
  const auto vector_1 = TwoDimensionalVector{{4, 5}, {0, 0}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, -10}};
  const auto expect_common_point = Point{0, 0};

  const std::optional<Point> actual_common_point =
      FindCommonPointOfVectors(vector_1, vector_2);

  ASSERT_TRUE(actual_common_point);
  ASSERT_EQ(expect_common_point, *actual_common_point);
}

TEST(VectorHelperTest,
     FindCommonPointOfVectorsShouldReturnPairWithFirstAsFalseIfNoCommonPoint) {
  const auto vector_1 = TwoDimensionalVector{{1, 2}, {-3, -4}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {-3, -10}};

  ASSERT_FALSE(FindCommonPointOfVectors(vector_1, vector_2));
}
