#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"
#include "../../src/visitor/illegal_node_checker.h"

class IllegalNodeCheckerTest : public ::testing::Test {
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

  Circle circle_{&circle_vector_};
  Rectangle rectangle_{&rectangle_vector_1, &rectangle_vector_2};
  Triangle triangle_{&triangle_vector_1_, &triangle_vector_2_};

  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  CompoundShape level_two_compound_{{&rectangle_, &triangle_}};
  CompoundShape level_one_compound_{{&circle_, &level_two_compound_}};

  IllegalNodeChecker checker_{};
};

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnTriangle) {
  checker_.visitTriangle(&triangle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnRectangle) {
  checker_.visitRectangle(&rectangle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnCircle) {
  checker_.visitCircle(&circle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnLegalCompoundShape) {
  CompoundShape legal_shape = level_one_compound_;
  checker_.visitCompoundShape(&legal_shape);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}