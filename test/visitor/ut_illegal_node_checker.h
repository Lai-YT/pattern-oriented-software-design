#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"
#include "../../src/visitor/illegal_node_checker.h"

class IllegalNodeCheckerTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Circle* circle_ = new Circle{{{1, 2}, {-3, 5}}};
  Rectangle* rectangle_ = new Rectangle{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle* triangle_ = new Triangle{{{0, 0}, {30, 0}}, {{30, 40}, {30, 0}}};

  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  Shape* level_two_compound_ = new CompoundShape{{rectangle_, triangle_}};
  CompoundShape level_one_compound_{{circle_, level_two_compound_}};

  IllegalNodeChecker checker_{};
};

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnTriangle) {
  checker_.visitTriangle(triangle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnRectangle) {
  checker_.visitRectangle(rectangle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnCircle) {
  checker_.visitCircle(circle_);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}

TEST_F(IllegalNodeCheckerTest, TestIsIllegalShouldBeFalseOnLegalCompoundShape) {
  /* don't copy, it's shallow */
  CompoundShape* legal_shape = &level_one_compound_;
  checker_.visitCompoundShape(legal_shape);

  auto is_illegal = checker_.isIllegal();

  ASSERT_FALSE(is_illegal);
}
