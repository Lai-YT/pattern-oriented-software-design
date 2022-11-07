#include <gtest/gtest.h>

#include <exception>
#include <set>

#include "../src/bounding_box.h"
#include "../src/point.h"

class BoundingBoxTest : public ::testing::Test {
 private:
  std::set<const Point*> points_ = {new Point{153, 183}, new Point{127, 196},
                                    new Point{143, 140}, new Point{108, 120},
                                    new Point{190, 121}};

 protected:
  BoundingBox bounding_box_{points_};

  ~BoundingBoxTest() {
    DeletePoints_(points_);
  }

  void DeletePoints_(std::set<const Point*>& points) {
    for (const Point* p : points) {
      delete p;
    }
  }
};

TEST_F(BoundingBoxTest, CreateBoundingBoxWithNoPointsShouldThrowRuntimeError) {
  ASSERT_THROW({ BoundingBox({/* empty set */}); }, std::runtime_error);
}

TEST_F(BoundingBoxTest, TestUpperRight) {
  ASSERT_EQ(Point(190, 196), bounding_box_.upper_right());
}

TEST_F(BoundingBoxTest, TestUpperRightPointerAliasMax) {
  ASSERT_EQ(Point(190, 196), *bounding_box_.max());
}

TEST_F(BoundingBoxTest, TestLowerLeft) {
  ASSERT_EQ(Point(108, 120), bounding_box_.lower_left());
}

TEST_F(BoundingBoxTest, TestLowerLeftPointerAliasMin) {
  ASSERT_EQ(Point(108, 120), *bounding_box_.min());
}

TEST_F(BoundingBoxTest, TestCollideShouldBeTrueIfOverlapped) {
  auto points =
      std::set<const Point*>{new Point{150, 170}, new Point{210, 180}};
  auto bb = BoundingBox{points};

  ASSERT_TRUE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfAdjacentOutside) {
  auto points =
      std::set<const Point*>{new Point{190, 170}, new Point{210, 300}};
  auto bb = BoundingBox{points};

  ASSERT_TRUE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfAdjacentInside) {
  auto points =
      std::set<const Point*>{new Point{180, 196}, new Point{130, 130}};
  auto bb = BoundingBox{points};

  ASSERT_TRUE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfEntirelyOverlapped) {
  ASSERT_TRUE(bounding_box_.collide(&bounding_box_));
}

TEST_F(BoundingBoxTest, DistanceToSelfShouldBeZero) {
  const double distance_to_self = bounding_box_.distance(&bounding_box_);

  const double expected = 0;
  ASSERT_NEAR(expected, distance_to_self, 0.001);
}
