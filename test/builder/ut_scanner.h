#include <gtest/gtest.h>

#include <string>

#include "../../src/builder/scanner.h"

/* To learn how std::stod works. */
TEST(StodTest, TestConvertDoubleWithCommaEnding) {
  std::string::size_type length = 0;

  const double actual = std::stod(" 1.00,", &length);

  ASSERT_NEAR(1, actual, 0.001);
  ASSERT_EQ(5, length);
}

class ScannerTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;
};

TEST_F(ScannerTest, TestNextOnVector) {
  const std::string input = "Vector ((1.00, 2.00), (-3.00, 5.00))";
  auto scanner = Scanner{input};

  ASSERT_EQ("Vector", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_NEAR(1, scanner.nextDouble(), DELTA);
  ASSERT_EQ(",", scanner.next());
  ASSERT_NEAR(2, scanner.nextDouble(), DELTA);
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(",", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_NEAR(-3, scanner.nextDouble(), DELTA);
  ASSERT_EQ(",", scanner.next());
  ASSERT_NEAR(5, scanner.nextDouble(), DELTA);
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_TRUE(scanner.isDone());
}

TEST_F(ScannerTest, TestNextOnCircle) {
  const std::string input = "Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))";
  auto scanner = Scanner{input};

  ASSERT_EQ("Circle", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ("Vector", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_NEAR(1, scanner.nextDouble(), DELTA);
  ASSERT_EQ(",", scanner.next());
  ASSERT_NEAR(2, scanner.nextDouble(), DELTA);
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(",", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_NEAR(-3, scanner.nextDouble(), DELTA);
  ASSERT_EQ(",", scanner.next());
  ASSERT_NEAR(5, scanner.nextDouble(), DELTA);
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_TRUE(scanner.isDone());
}

TEST_F(ScannerTest, TestNextOnCompoundShape) {
  /* clang-format off */
  const std::string input =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  auto scanner = Scanner{input};

  ASSERT_EQ("CompoundShape", scanner.next());
  ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
      ASSERT_EQ("Vector", scanner.next());
      ASSERT_EQ("(", scanner.next());
      ASSERT_EQ("(", scanner.next());
      ASSERT_NEAR(1, scanner.nextDouble(), DELTA);
      ASSERT_EQ(",", scanner.next());
      ASSERT_NEAR(2, scanner.nextDouble(), DELTA);
      ASSERT_EQ(")", scanner.next());
      ASSERT_EQ(",", scanner.next());
      ASSERT_EQ("(", scanner.next());
      ASSERT_NEAR(-3, scanner.nextDouble(), DELTA);
      ASSERT_EQ(",", scanner.next());
      ASSERT_NEAR(5, scanner.nextDouble(), DELTA);
      ASSERT_EQ(")", scanner.next());
      ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("CompoundShape", scanner.next());
    ASSERT_EQ("(", scanner.next());
      ASSERT_EQ("Rectangle", scanner.next());
      ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("Vector", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(3, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("Vector", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(4, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(")", scanner.next());
      ASSERT_EQ(")", scanner.next());
      ASSERT_EQ(",", scanner.next());
      ASSERT_EQ("Triangle", scanner.next());
      ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("Vector", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(3, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("Vector", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(3, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(4, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(",", scanner.next());
        ASSERT_EQ("(", scanner.next());
        ASSERT_NEAR(3, scanner.nextDouble(), DELTA);
        ASSERT_EQ(",", scanner.next());
        ASSERT_NEAR(0, scanner.nextDouble(), DELTA);
        ASSERT_EQ(")", scanner.next());
        ASSERT_EQ(")", scanner.next());
      ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_TRUE(scanner.isDone());
  /* clang-format on */
}
