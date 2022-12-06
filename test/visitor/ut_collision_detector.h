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
 private:
  const Triangle shape_to_detect_with_{{{1, 2}, {1, 5}}, {{1, 2}, {-3, 2}}};

 protected:
  CollisionDetector detector_{&shape_to_detect_with_};
  Circle collided_circle_{{{1, 2}, {-3, 5}}};
  Circle uncollided_circle_{{{10, 20}, {13, 16}}};
  Triangle collided_triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  Triangle uncollided_triangle_{{{10, 10}, {13, 10}}, {{13, 14}, {13, 10}}};
  Rectangle collided_rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Rectangle uncollided_rectangle_{{{10, 10}, {13, 10}}, {{10, 10}, {10, 14}}};
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
