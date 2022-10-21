#include <gtest/gtest.h>

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

TEST_F(BoundingBoxTest, TestUpperRight) {
  ASSERT_EQ(Point(190, 196), bounding_box_.upper_right());
}

TEST_F(BoundingBoxTest, TestLowerLeft) {
  ASSERT_EQ(Point(108, 120), bounding_box_.lower_left());
}

TEST_F(BoundingBoxTest, TestCollideShouldBeTrueIfOverlapped) {
  auto points =
      std::set<const Point*>{new Point{150, 170}, new Point{210, 180}};
  auto bb = BoundingBox{points};

  ASSERT_TRUE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldFalseIfAlignedOutside) {
  auto points =
      std::set<const Point*>{new Point{190, 170}, new Point{210, 300}};
  auto bb = BoundingBox{points};

  ASSERT_FALSE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfAlignedInside) {
  auto points =
      std::set<const Point*>{new Point{180, 196}, new Point{130, 130}};
  auto bb = BoundingBox{points};

  ASSERT_TRUE(bounding_box_.collide(&bb));
  DeletePoints_(points);
}

TEST_F(BoundingBoxTest, TestCollideShouldBeShouldTrueIfEntirelyOverlapped) {
  ASSERT_TRUE(bounding_box_.collide(&bounding_box_));
}
