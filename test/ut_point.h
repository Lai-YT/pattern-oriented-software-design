#include <gtest/gtest.h>

#include <string>

#include "../src/point.h"

TEST(PointTest, CheckXYSetProperly) {
  const auto p = Point{2, -3};

  EXPECT_EQ(2, p.x());
  EXPECT_EQ(-3, p.y());
}

TEST(PointTest, TestInfoOnIntegerXY) {
  const auto p = Point{2, -3};

  const std::string info = p.info();

  ASSERT_EQ("(2, -3)", info);
}

TEST(PointTest, TestInfoOnDoubleXYShouldRoundToTwoDecimalPlaces) {
  const auto p = Point{-4.586, -3.471};

  const std::string info = p.info();

  ASSERT_EQ("(-4.59, -3.47)", info);
}
