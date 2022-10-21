#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/visitor/collision_detector.h"

class CollisionDetectorTest : public ::testing::Test {
 protected:
 private:
  Point upper_right_{1, 5};
  Point lower_left_{-3, 2};

  const Point collided_circle_vector_head_{1, 2};
  const Point collided_circle_vector_tail_{-3, 5};
  const TwoDimensionalVector collided_circle_vector_{
      &collided_circle_vector_head_, &collided_circle_vector_tail_};

  const Point uncollided_circle_vector_head_{10, 20};
  const Point uncollided_circle_vector_tail_{13, 16};
  const TwoDimensionalVector uncollided_circle_vector_{
      &uncollided_circle_vector_head_, &uncollided_circle_vector_tail_};

  const Point collided_triangle_vector_head_1_{0, 0};
  const Point collided_triangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector collided_triangle_vector_1_{
      &collided_triangle_vector_head_1_, &collided_triangle_vector_tail_1_};
  const Point collided_triangle_vector_head_2_{3, 4};
  const Point collided_triangle_vector_tail_2_{3, 0};
  const TwoDimensionalVector collided_triangle_vector_2_{
      &collided_triangle_vector_head_2_, &collided_triangle_vector_tail_2_};

  const Point uncollided_triangle_vector_head_1_{10, 10};
  const Point uncollided_triangle_vector_tail_1_{13, 10};
  const TwoDimensionalVector uncollided_triangle_vector_1_{
      &uncollided_triangle_vector_head_1_, &uncollided_triangle_vector_tail_1_};
  const Point uncollided_triangle_vector_head_2_{13, 14};
  const Point uncollided_triangle_vector_tail_2_{13, 10};
  const TwoDimensionalVector uncollided_triangle_vector_2_{
      &uncollided_triangle_vector_head_2_, &uncollided_triangle_vector_tail_2_};

  const Point collided_rectangle_vector_head_1_{0, 0};
  const Point collided_rectangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector collided_rectangle_vector_1_{
      &collided_rectangle_vector_head_1_, &collided_rectangle_vector_tail_1_};
  const Point collided_rectangle_vector_head_2_{0, 0};
  const Point collided_rectangle_vector_tail_2_{0, 4};
  const TwoDimensionalVector collided_rectangle_vector_2_{
      &collided_rectangle_vector_head_2_, &collided_rectangle_vector_tail_2_};

  const Point uncollided_rectangle_vector_head_1_{10, 10};
  const Point uncollided_rectangle_vector_tail_1_{13, 10};
  const TwoDimensionalVector uncollided_rectangle_vector_1_{
      &uncollided_rectangle_vector_head_1_,
      &uncollided_rectangle_vector_tail_1_};
  const Point uncollided_rectangle_vector_head_2_{10, 10};
  const Point uncollided_rectangle_vector_tail_2_{10, 14};
  const TwoDimensionalVector uncollided_rectangle_vector_2_{
      &uncollided_rectangle_vector_head_2_,
      &uncollided_rectangle_vector_tail_2_};

 protected:
  CollisionDetector detector_{{&upper_right_, &lower_left_}};
  Circle collided_circle_{&collided_circle_vector_};
  Circle uncollided_circle_{&uncollided_circle_vector_};
  Triangle collided_triangle_{&collided_triangle_vector_1_,
                              &collided_triangle_vector_2_};
  Triangle uncollided_triangle_{&uncollided_triangle_vector_1_,
                                &uncollided_triangle_vector_2_};
  Rectangle collided_rectangle_{&collided_rectangle_vector_1_,
                                &collided_rectangle_vector_2_};
  Rectangle uncollided_rectangle_{&uncollided_rectangle_vector_1_,
                                  &uncollided_rectangle_vector_2_};
};

TEST_F(CollisionDetectorTest,
       VisitCircleOnCollidedShouldHaveCollidedShapesContainExcatlyThatCircle) {
  detector_.visitCircle(&collided_circle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_EQ(1, collided_shapes.size());
  ASSERT_EQ(&collided_circle_, collided_shapes.front());
}

TEST_F(CollisionDetectorTest,
       VisitCircleOnUncollidedShouldHaveCollidedShapesEmpty) {
  detector_.visitCircle(&uncollided_circle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_TRUE(collided_shapes.empty());
}

TEST_F(
    CollisionDetectorTest,
    VisitTriangleOnCollidedShouldHaveCollidedShapesContainExcatlyThatTriangle) {
  detector_.visitTriangle(&collided_triangle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_EQ(1, collided_shapes.size());
  ASSERT_EQ(&collided_triangle_, collided_shapes.front());
}

TEST_F(CollisionDetectorTest,
       VisitTriangleOnUncollidedShouldHaveCollidedShapesEmpty) {
  detector_.visitTriangle(&uncollided_triangle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_TRUE(collided_shapes.empty());
}

TEST_F(
    CollisionDetectorTest,
    VisitRectangleOnCollidedShouldHaveCollidedShapesContainExcatlyThatTriangle) {
  detector_.visitRectangle(&collided_rectangle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_EQ(1, collided_shapes.size());
  ASSERT_EQ(&collided_rectangle_, collided_shapes.front());
}

TEST_F(CollisionDetectorTest,
       VisitRectangleOnUncollidedShouldHaveCollidedShapesEmpty) {
  detector_.visitRectangle(&uncollided_rectangle_);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_TRUE(collided_shapes.empty());
}

TEST_F(
    CollisionDetectorTest,
    VisitCompoundShapeOnCollidedShouldHaveCollidedShapesContainThoseCollidedChildShapes) {
  auto level_two_compound =
      CompoundShape{{&uncollided_circle_, &collided_rectangle_}};
  auto level_one_compound = CompoundShape{
      {&collided_circle_, &collided_triangle_, &level_two_compound}};

  detector_.visitCompoundShape(&level_one_compound);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_EQ(3, collided_shapes.size());
  ASSERT_EQ(&collided_circle_, collided_shapes.at(0));
  ASSERT_EQ(&collided_triangle_, collided_shapes.at(1));
  ASSERT_EQ(&collided_rectangle_, collided_shapes.at(2));
}

TEST_F(CollisionDetectorTest,
       VisitCompoundShapeOnUncollidedShouldHaveCollidedShapesEmpty) {
  auto level_two_compound =
      CompoundShape{{&uncollided_rectangle_, &uncollided_circle_}};
  auto level_one_compound = CompoundShape{
      {&uncollided_circle_, &uncollided_triangle_, &level_two_compound}};

  detector_.visitCompoundShape(&level_one_compound);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_TRUE(collided_shapes.empty());
}
