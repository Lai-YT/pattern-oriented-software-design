#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/visitor/closest_shape_finder.h"

class ClosestShapeFinderTest : public ::testing::Test {
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
  const Point triangle_vector_tail_1_{30, 0};
  const TwoDimensionalVector triangle_vector_1_{&triangle_vector_head_1_,
                                                &triangle_vector_tail_1_};
  const Point triangle_vector_head_2_{30, 40};
  const Point triangle_vector_tail_2_{30, 0};
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
};

TEST_F(ClosestShapeFinderTest,
       ClosestShapeOnNonCompoundShapeShouldBeThatShape) {
  auto closest_finder = ClosestShapeFinder{&circle_};

  rectangle_.accept(&closest_finder);

  ASSERT_EQ(&circle_, closest_finder.getClosestShape());
}

TEST_F(ClosestShapeFinderTest, ClosestShapeOnCompoundShape) {
  auto closest_finder = ClosestShapeFinder{&level_one_compound_};

  rectangle_.accept(&closest_finder);
  ASSERT_EQ(&rectangle_, closest_finder.getClosestShape());
  ASSERT_EQ(&level_two_compound_, closest_finder.getParent());
}
