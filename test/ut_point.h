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

TEST(PointTest, SwappedXYShouldBeEqual) {
  const auto a = Point{2, -3};
  const auto b = Point{-3, 2};

  ASSERT_TRUE(a == b);
}

TEST(PointTest, TestEqualityOnSelfComparison) {
  const auto p = Point{2, -3};

  ASSERT_TRUE(p == p);
}

TEST(PointTest, TestEqualityOnDifferentXY) {
  const auto a = Point{2, -3};
  const auto b = Point{2, 4};

  ASSERT_FALSE(a == b);
}

TEST(PointTest, TestInequalityOnDifferentXY) {
  const auto a = Point{2, -3};
  const auto b = Point{2, 4};

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
