#include <gtest/gtest.h>

#include <functional>
#include <set>

#include "../src/circle.h"
#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/list_iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 private:
  const Point vector_head_ = Point{1, 2};
  const Point vector_tail_ = Point{-3, 5};
  const TwoDimensionalVector vector_{&vector_head_, &vector_tail_};

 protected:
  const double DELTA = 0.001;

  Circle circle_{&vector_};
};

TEST_F(CircleTest, TestRadius) {
  ASSERT_NEAR(5, circle_.radius(), DELTA);
}

TEST_F(CircleTest, TestArea) {
  ASSERT_NEAR(78.540, circle_.area(), DELTA);
}

TEST_F(CircleTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_.perimeter(), DELTA);
}

TEST_F(CircleTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_.info());
}

TEST_F(CircleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ circle_.addShape(&circle_); }, Shape::ShapeInaddibleException);
}

TEST_F(CircleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ circle_.deleteShape(&circle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(CircleTest, GetPointsShouldReturnUpperRightAndLowerLeft) {
  const std::set<Point*> bounding_points = circle_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the value of points
   * into another set. */
  auto upper_right = Point{6, 7};
  auto lower_left = Point{-4, -3};
  auto bounding_points_with_value_as_compare =
      std::set<Point*, std::function<bool(Point*, Point*)>>{
          bounding_points.begin(), bounding_points.end(),
          [](Point* p1, Point* p2) { return p1->info() < p2->info(); }};
  ASSERT_EQ(2, bounding_points.size());
  ASSERT_TRUE(bounding_points_with_value_as_compare.find(&upper_right) !=
              bounding_points_with_value_as_compare.end());
  ASSERT_TRUE(bounding_points_with_value_as_compare.find(&lower_left) !=
              bounding_points_with_value_as_compare.end());
}

class CirclePolymorphismTest : public CircleTest {
 protected:
  Shape& circle_{CircleTest::circle_};
};

TEST_F(CirclePolymorphismTest, TestArea) {
  ASSERT_NEAR(78.540, circle_.area(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(31.416, circle_.perimeter(), DELTA);
}

TEST_F(CirclePolymorphismTest, TestInfo) {
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))", circle_.info());
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithBfsIteratorFactoryShouldIsDone) {
  const auto factory = BFSIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
