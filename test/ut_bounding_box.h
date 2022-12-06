#include <gtest/gtest.h>

#include <exception>
#include <set>

#include "../src/bounding_box.h"
#include "../src/point.h"

class BoundingBoxTest : public ::testing::Test {
 protected:
  BoundingBox bounding_box_{
      {{153, 183}, {127, 196}, {143, 140}, {108, 120}, {190, 121}}};
};

TEST_F(BoundingBoxTest, CreateBoundingBoxWithNoPointsShouldThrowRuntimeError) {
  ASSERT_THROW({ BoundingBox({/* empty set */}); }, std::runtime_error);
}

TEST_F(BoundingBoxTest, TestUpperRight) {
  ASSERT_EQ(Point(190, 196), bounding_box_.upper_right());
}

TEST_F(BoundingBoxTest, TestUpperRightPointerAliasMax) {
  ASSERT_EQ(Point(190, 196), bounding_box_.max());
}

TEST_F(BoundingBoxTest, TestLowerLeft) {
  ASSERT_EQ(Point(108, 120), bounding_box_.lower_left());
}

TEST_F(BoundingBoxTest, TestLowerLeftPointerAliasMin) {
  ASSERT_EQ(Point(108, 120), bounding_box_.min());
}

TEST_F(BoundingBoxTest, TestCollideShouldBeTrueIfOverlapped) {
  auto bb = BoundingBox{{{150, 170}, {210, 180}}};

  ASSERT_TRUE(bounding_box_.collide(&bb));
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfAdjacentOutside) {
  auto bb = BoundingBox{{{190, 170}, {210, 300}}};

  ASSERT_TRUE(bounding_box_.collide(&bb));
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfAdjacentInside) {
  auto bb = BoundingBox{{{180, 196}, {130, 130}}};

  ASSERT_TRUE(bounding_box_.collide(&bb));
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfEntirelyOverlapped) {
  ASSERT_TRUE(bounding_box_.collide(&bounding_box_));
}

TEST_F(BoundingBoxTest, DistanceToSelfShouldBeZero) {
  const double distance_to_self = bounding_box_.distance(&bounding_box_);

  const double expected = 0;
  ASSERT_NEAR(expected, distance_to_self, 0.001);
}
