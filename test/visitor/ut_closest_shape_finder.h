#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/visitor/closest_shape_finder.h"

class ClosestShapeFinderTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {30, 0}}, {{30, 40}, {30, 0}}};
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
