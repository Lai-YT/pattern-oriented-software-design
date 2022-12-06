#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/illegal_node_iterator.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"

class IllegalNodeIteratorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};

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

TEST_F(IllegalNodeIteratorTest, TestIsDoneShouldBeTrueOnLegalShape) {
  CompoundShape legal_shape = level_one_compound_;

  auto itr = IllegalNodeIterator{&legal_shape};
  bool is_done = itr.isDone();

  ASSERT_TRUE(is_done);
}

TEST_F(IllegalNodeIteratorTest, TestIsDoneShouldBeTrueOnNonCompoundShape) {
  Rectangle non_compound_shape = rectangle_;

  auto itr = IllegalNodeIterator{&non_compound_shape};
  bool is_done = itr.isDone();

  ASSERT_TRUE(is_done);
}
