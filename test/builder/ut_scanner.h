#include <gtest/gtest.h>

#include <regex>
#include <string>

#include "../../src/builder/scanner.h"

/* To learn how std::stod works. */
TEST(StodTest, TestConvertDoubleWithCommaEnding) {
  std::string::size_type length = 0;

  const double actual = std::stod(" 1.00,", &length);

  ASSERT_NEAR(1, actual, 0.001);
  ASSERT_EQ(5, length);
}

/* To learn how regex in C++ works and whether the expression is correct. */
class RegexOnFloatingPointNumberTest
    : public testing::TestWithParam<std::string> {};

INSTANTIATE_TEST_SUITE_P(PossibleForms, RegexOnFloatingPointNumberTest,
                         testing::Values("450.945", "450", "450.", ".945",
                                         "+450.945", "-450.945"));

TEST_P(RegexOnFloatingPointNumberTest, TestCorrectnessOfRegex) {
  const std::string target = GetParam();
  const auto subject =
      std::string{"Here we have " + target + " as the target."};
  const int first_match_char_position = 13;
  auto match = std::smatch{};

  const auto regex_for_floating_points =
      std::regex{R"([-+]?(?:\d+(?:\.\d*)?|\.\d+))"};

  const bool has_floating_point_number =
      std::regex_search(subject, match, regex_for_floating_points);
  ASSERT_TRUE(has_floating_point_number);
  EXPECT_EQ(1, match.size());
  ASSERT_EQ(target, match.str());
  ASSERT_EQ(target.size(), match.length());
  ASSERT_EQ(13, match.position());
}

class ScannerTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;
};

TEST_F(ScannerTest, TestNextDoubleOnVector) {
  const std::string input = "Vector ((1.00, 2.00), (-3.00, 5.00))";
  auto scanner = Scanner{input};

  ASSERT_NEAR(1, scanner.nextDouble(), DELTA);
  ASSERT_NEAR(2, scanner.nextDouble(), DELTA);
  ASSERT_NEAR(-3, scanner.nextDouble(), DELTA);
  ASSERT_NEAR(5, scanner.nextDouble(), DELTA);
}

TEST_F(ScannerTest, TestNextOnVector) {
  const std::string input = "Vector ((1.00, 2.00), (-3.00, 5.00))";
  auto scanner = Scanner{input};

  ASSERT_EQ("Vector", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ(",", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(",", scanner.next());
  ASSERT_EQ("(", scanner.next());
  ASSERT_EQ(",", scanner.next());
  ASSERT_EQ(")", scanner.next());
  ASSERT_EQ(")", scanner.next());
}

TEST_F(ScannerTest, TestNextWithNextDoubleOnVector) {
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

TEST_F(ScannerTest, TestNextWithNextDoubleOnCircle) {
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

TEST_F(ScannerTest, TestNextWithNextDoubleOnCompoundShape) {
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

TEST_F(ScannerTest, TestNextShouldThrowExceptionWhenIsDone) {
  const std::string input = "Vector ((1.00, 2.00), (-3.00, 5.00))";
  const int number_of_tokens = 10;
  auto scanner = Scanner{input};
  for (size_t i = 0; i < number_of_tokens; i++) {
    scanner.next();
  }

  ASSERT_THROW(scanner.next(), Scanner::ScanIsDoneException);
}

TEST_F(ScannerTest, TestNextDoubleShouldThrowExceptionWhenIsDone) {
  const std::string input = "Vector ((1.00, 2.00), (-3.00, 5.00))";
  const int number_of_doubles = 4;
  auto scanner = Scanner{input};
  for (size_t i = 0; i < number_of_doubles; i++) {
    scanner.nextDouble();
  }

  ASSERT_THROW(scanner.nextDouble(), Scanner::ScanIsDoneException);
}
