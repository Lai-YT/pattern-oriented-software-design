#include <gtest/gtest.h>

#include <string>

#include "../src/point.h"

TEST(PointTest, CheckXYSetProperlyByConstructor) {
  const auto p = Point{2, -3};

  EXPECT_EQ(2, p.x());
  EXPECT_EQ(-3, p.y());
}

TEST(PointTest, TestInfoOnIntegerXY) {
  const auto p = Point{2, -3};

  ASSERT_EQ("(2.00, -3.00)", p.info());
}

TEST(PointTest, TestInfoOnDoubleXYRoundsToTwoDecimalPlaces) {
  const auto p = Point{-4.586, -3.471};

  ASSERT_EQ("(-4.59, -3.47)", p.info());
}

TEST(PointTest, TestInfoOnDoubleFillWithZerosIfNotEnoughDecimalNumber) {
  const auto p = Point{-3.0, 4.1};

  ASSERT_EQ("(-3.00, 4.10)", p.info());
}

TEST(PointTest, TestEqualityOnSameXY) {
  const auto a = Point{2, -3};
  const auto b = Point{2, -3};

  ASSERT_TRUE(a == b);
}

TEST(PointTest, TestEqualityOnSameDoubleXY) {
  const auto a = Point{3.16, 1.99};
  const auto b = Point{3.16, 1.99};

  ASSERT_TRUE(a == b);
}

TEST(PointTest, TestEqualityOnSelfComparison) {
  const auto p = Point{2, -3};

  ASSERT_TRUE(p == p);
}

TEST(PointTest, TestEqualityOnDifferentXY) {
  const auto a = Point{2, -3};
  const auto b = Point{-3, 2};

  ASSERT_FALSE(a == b);
}

TEST(PointTest, TestInequalityOnDifferentXY) {
  const auto a = Point{2, -3};
  const auto b = Point{-3, 2};

  ASSERT_TRUE(a != b);
}

TEST(PointTest, TestInequalityOnSameXY) {
  const auto a = Point{2, -3};
  const auto b = Point{2, -3};

  ASSERT_FALSE(a != b);
}

TEST(PointTest, TestInequalityOnSelfComparison) {
  const auto p = Point{2, -3};

  ASSERT_FALSE(p != p);
}

TEST(PointTest, TestLessThanOnSameY) {
  const auto smaller_x = Point{2, -3};
  const auto larger_x = Point{3, -3};

  ASSERT_TRUE(smaller_x < larger_x);
  ASSERT_FALSE(larger_x < smaller_x);
}

TEST(PointTest, TestLessThanOnSameX) {
  const auto smaller_y = Point{2, -3};
  const auto larger_y = Point{2, -2};

  ASSERT_TRUE(smaller_y < larger_y);
  ASSERT_FALSE(larger_y < smaller_y);
}

TEST(PointTest, TestDistance) {
  const auto a = Point{0, 0};
  const auto b = Point{-3, 4};

  const double distance = a.distance(b);

  const double expected = 5;
  ASSERT_NEAR(expected, distance, 0.001);
}
