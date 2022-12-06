#include <gtest/gtest.h>

#include <memory>
#include <set>

#include "../src/circle.h"
#include "../src/iterator/factory/iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/two_dimensional_vector.h"

class CircleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Circle circle_{{{1, 2}, {-3, 5}}};
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
  const auto upper_right = Point{6, 7};
  const auto lower_left = Point{-4, -3};

  const std::set<Point> bounding_points = circle_.getPoints();

  ASSERT_EQ(2, bounding_points.size());
  ASSERT_TRUE(bounding_points.find(upper_right) != bounding_points.end());
  ASSERT_TRUE(bounding_points.find(lower_left) != bounding_points.end());
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

  auto it = std::unique_ptr<Iterator>{circle_.createIterator(factory)};

  ASSERT_TRUE(it->isDone());
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("DFS");

  auto it = std::unique_ptr<Iterator>{circle_.createIterator(factory)};

  ASSERT_TRUE(it->isDone());
}

TEST_F(CirclePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("List");

  auto it = std::unique_ptr<Iterator>{circle_.createIterator(factory)};

  ASSERT_TRUE(it->isDone());
}
