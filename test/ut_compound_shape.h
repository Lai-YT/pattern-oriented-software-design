#include <gtest/gtest.h>

#include <string>

#include "../src/circle.h"
#include "../src/compound_shape.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class CompoundShapeTest : public ::testing::Test {
 private:
  const Point circle_vector_head_{1, 2};
  const Point circle_vector_tail_{-3, 5};
  const TwoDimensionalVector circle_vector_{&circle_vector_head_,
                                            &circle_vector_tail_};
  const Point rectangle_vector_head_1_{0, 0};
  const Point rectangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector rectangle_vector_1{&rectangle_vector_head_1_,
                                                &rectangle_vector_tail_1_};
  const Point rectangle_vector_head_2_{0, 0};
  const Point rectangle_vector_tail_2_{0, 4};
  const TwoDimensionalVector rectangle_vector_2{&rectangle_vector_head_2_,
                                                &rectangle_vector_tail_2_};
  const Point triangle_vector_head_1_{0, 0};
  const Point triangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector triangle_vector_1_{&triangle_vector_head_1_,
                                                &triangle_vector_tail_1_};
  const Point triangle_vector_head_2_{3, 4};
  const Point triangle_vector_tail_2_{3, 0};
  const TwoDimensionalVector triangle_vector_2_{&triangle_vector_head_2_,
                                                &triangle_vector_tail_2_};

  /* protected after private because non-static data members are initialized in
   * order of declaration in the class definition. */
 protected:
  const double DELTA = 0.001;

  const Circle circle_{&circle_vector_};
  const Rectangle rectangle_{&rectangle_vector_1, &rectangle_vector_2};
  const Triangle triangle_{&triangle_vector_1_, &triangle_vector_2_};
};

class CompoundShapeDepthOneTest : public CompoundShapeTest {
 protected:
  /*
   *     compound
   *     /   |   \
   *    cir  rec  tri
   */
  const CompoundShape compound_{{&circle_, &rectangle_, &triangle_}};
};

class CompoundShapeDepthTwoTest : public CompoundShapeTest {
 protected:
  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  const CompoundShape level_two_compound_{{&rectangle_, &triangle_}};
  const CompoundShape level_one_compound_{{&circle_, &level_two_compound_}};
};

TEST_F(CompoundShapeTest, TestConstructorTakingCStyleArrayShouldCompile) {
  const Shape* shapes[] = {&circle_, &rectangle_, &triangle_};
  const auto compound = CompoundShape{shapes, 3};
}

TEST_F(CompoundShapeDepthOneTest, TestArea) {
  const double actual = compound_.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthTwoTest, TestArea) {
  const double actual = level_one_compound_.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthOneTest, TestPerimeter) {
  const double actual = compound_.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthTwoTest, TestPerimeter) {
  const double actual = level_one_compound_.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthOneTest, TestInfo) {
  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
      ")";
  /* clang-format on */

  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestInfo) {
  const std::string actual = level_one_compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  /* clang-format on */

  ASSERT_EQ(expected, actual);
}
