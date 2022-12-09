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
       VisitCircleOnCollidedShouldHaveCollidedShapesContainExactlyThatCircle) {
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
    VisitTriangleOnCollidedShouldHaveCollidedShapesContainExactlyThatTriangle) {
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
    VisitRectangleOnCollidedShouldHaveCollidedShapesContainExactlyThatTriangle) {
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
  auto* uncollided_circle = new Circle{uncollided_circle_};
  auto* collided_rectangle = new Rectangle{collided_rectangle_};
  auto* collided_triangle = new Triangle{collided_triangle_};
  Shape* level_two_compound =
      new CompoundShape{{uncollided_circle, collided_rectangle}};
  auto level_one_compound =
      CompoundShape{{collided_triangle, level_two_compound}};

  detector_.visitCompoundShape(&level_one_compound);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_EQ(2, collided_shapes.size());
  ASSERT_EQ(collided_triangle, collided_shapes.at(0));
  ASSERT_EQ(collided_rectangle, collided_shapes.at(1));
}

TEST_F(CollisionDetectorTest,
       VisitCompoundShapeOnUncollidedShouldHaveCollidedShapesEmpty) {
  Shape* level_two_compound = new CompoundShape{
      {new Rectangle{uncollided_rectangle_}, new Circle{uncollided_circle_}}};
  auto level_one_compound =
      CompoundShape{{new Circle{uncollided_circle_},
                     new Triangle{uncollided_triangle_}, level_two_compound}};

  detector_.visitCompoundShape(&level_one_compound);

  std::vector<Shape*> collided_shapes = detector_.collidedShapes();
  ASSERT_TRUE(collided_shapes.empty());
}
