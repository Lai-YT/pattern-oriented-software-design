#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

class RectangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  RectangleTest()
      : vector_1_{TwoDimensionalVector(&vector_head_1_, &vector_tail_1_)},
        vector_2_{TwoDimensionalVector(&vector_head_2_, &vector_tail_2_)} {
    rectangle_ = new Rectangle{&vector_1_, &vector_2_};
  }

  virtual ~RectangleTest() override {
    delete rectangle_;
  }

  Rectangle* rectangle_;

 private:
  const Point vector_head_1_ = Point{0, 0};
  const Point vector_tail_1_ = Point{3, 0};
  const TwoDimensionalVector vector_1_;
  const Point vector_head_2_ = Point{0, 0};
  const Point vector_tail_2_ = Point{0, 4};
  const TwoDimensionalVector vector_2_;
};

TEST_F(RectangleTest, TestLength) {
  ASSERT_NEAR(3, rectangle_->length(), DELTA);
}

TEST_F(RectangleTest, TestWidth) {
  ASSERT_NEAR(4, rectangle_->width(), DELTA);
}

TEST_F(RectangleTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_->info());
}

TEST_F(RectangleTest, TestArea) {
  ASSERT_NEAR(12, rectangle_->area(), DELTA);
}

TEST_F(RectangleTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_->perimeter(), DELTA);
}

TEST_F(RectangleTest, PassingNonOrthognalSidesShouldThrowException) {
  const auto vector_head_1 = Point{0, 0};
  const auto vector_tail_1 = Point{3, 1};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{0, 0};
  const auto vector_tail_2 = Point{0, 4};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto rectangle = Rectangle(&vector_1, &vector_2); },
               Rectangle::NonOrthogonalSideException);
}

TEST_F(RectangleTest, PassingSidesWithNoCommonPointShouldThrowException) {
  const auto vector_head_1 = Point{1, 0};
  const auto vector_tail_1 = Point{3, 0};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{0, 0};
  const auto vector_tail_2 = Point{0, 4};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto rectangle = Rectangle(&vector_1, &vector_2); },
               Rectangle::NoCommonPointException);
}

TEST_F(RectangleTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = rectangle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

class RectanglePolymorphismTest : public RectangleTest {
 protected:
  RectanglePolymorphismTest() : RectangleTest{} {
    rectangle_ = RectangleTest::rectangle_;
  }

  Shape* rectangle_;
};

TEST_F(RectanglePolymorphismTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_->info());
}

TEST_F(RectanglePolymorphismTest, TestArea) {
  ASSERT_NEAR(12, rectangle_->area(), DELTA);
}

TEST_F(RectanglePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_->perimeter(), DELTA);
}

TEST_F(RectanglePolymorphismTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = rectangle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}
