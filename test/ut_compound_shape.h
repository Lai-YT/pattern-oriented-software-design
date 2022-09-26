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

TEST_F(CompoundShapeTest, TestAreaDepthOne) {
  /*
   *     compound
   *     /   |   \
   *    cir  rec  tri
   */
  const auto compound = CompoundShape{{&circle_, &rectangle_, &triangle_}};

  const double actual = compound.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeTest, TestAreaDepthTwo) {
  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  const auto level_two_compound = CompoundShape{{&rectangle_, &triangle_}};
  const auto level_one_compound =
      CompoundShape{{&circle_, &level_two_compound}};

  const double actual = level_one_compound.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeTest, TestPerimeterDepthOne) {
  /*
   *     compound
   *     /   |   \
   *    cir  rec  tri
   */
  const auto compound = CompoundShape{{&circle_, &rectangle_, &triangle_}};

  const double actual = compound.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeTest, TestPerimeterDepthTwo) {
  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  const auto level_two_compound = CompoundShape{{&rectangle_, &triangle_}};
  const auto level_one_compound =
      CompoundShape{{&circle_, &level_two_compound}};

  const double actual = level_one_compound.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeTest, TestInfoDepthOne) {
  /*
   *     compound
   *     /   |   \
   *    cir  rec  tri
   */
  const auto compound = CompoundShape{{&circle_, &rectangle_, &triangle_}};

  const std::string actual = compound.info();
  const std::string expected =
      "CompoundShape ("
      "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00))), "
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))"
      ")";

  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeTest, TestInfoDepthTwo) {
  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  const auto level_two_compound = CompoundShape{{&rectangle_, &triangle_}};
  const auto level_one_compound =
      CompoundShape{{&circle_, &level_two_compound}};

  const std::string actual = level_one_compound.info();
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
