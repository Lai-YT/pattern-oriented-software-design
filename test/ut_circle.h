#include <gtest/gtest.h>

#include "../src/circle.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  CircleTest() : vector_{TwoDimensionalVector{&vector_head_, &vector_tail_}} {
    circle_ = new Circle{&vector_};
  }

  virtual ~CircleTest() override {
    delete circle_;
  }

  Circle* circle_;

 private:
  const TwoDimensionalVector vector_;
  const Point vector_head_ = Point{1, 2};
  const Point vector_tail_ = Point{-3, 5};
};

TEST_F(CircleTest, TestRadius) {
  ASSERT_NEAR(5, circle_->radius(), DELTA);
}

TEST_F(CircleTest, TestArea) {
  ASSERT_NEAR(78.540, circle_->area(), DELTA);
}

TEST_F(CircleTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_->perimeter(), DELTA);
}

TEST_F(CircleTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_->info());
}

TEST_F(CircleTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = circle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

class CirclePolymorphismTest : public CircleTest {
 protected:
  CirclePolymorphismTest() : CircleTest{} {
    circle_ = CircleTest::circle_;
  }

  Shape* circle_;
};

TEST_F(CirclePolymorphismTest, TestArea) {
  ASSERT_NEAR(78.540, circle_->area(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_->perimeter(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_->info());
}

TEST_F(CirclePolymorphismTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = circle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}
