#include <gtest/gtest.h>

#include <functional>
#include <set>

#include "../src/circle.h"
#include "../src/iterator/factory/iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 private:
  const Point vector_head_{1, 2};
  const Point vector_tail_{-3, 5};
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
  const std::set<const Point*> bounding_points = circle_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the points
   * into another set which compares with value. */
  const auto bounding_points_with_value_as_compare =
      std::set<const Point*, std::function<bool(const Point*, const Point*)>>{
          bounding_points.begin(), bounding_points.end(),
          [](const Point* p1, const Point* p2) {
            return p1->info() < p2->info();
          }};
  const auto upper_right = Point{6, 7};
  const auto lower_left = Point{-4, -3};
  ASSERT_EQ(2, bounding_points.size());
  ASSERT_TRUE(bounding_points_with_value_as_compare.find(&upper_right) !=
              bounding_points_with_value_as_compare.end());
  ASSERT_TRUE(bounding_points_with_value_as_compare.find(&lower_left) !=
              bounding_points_with_value_as_compare.end());
  for (const Point* p : bounding_points) {
    delete p;
  }
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
  const IteratorFactory* factory = IteratorFactory::getInstance("BFS");

  Iterator* it = circle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("DFS");

  Iterator* it = circle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("List");

  Iterator* it = circle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
