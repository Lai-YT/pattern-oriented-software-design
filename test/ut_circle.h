#include <gtest/gtest.h>

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

TEST_F(CircleTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = circle_.createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

TEST_F(CircleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ circle_.addShape(&circle_); }, Shape::ShapeInaddibleException);
}

TEST_F(CircleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ circle_.deleteShape(&circle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(CircleTest, CreateIteratorWithBfsIteratorFactoryShouldgetNullIterator) {
  const auto factory = BFSIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CircleTest, CreateIteratorWithDfsIteratorFactoryShouldGetNullIterator) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(CircleTest, CreateIteratorWithListIteratorFactoryShouldGetNullIterator) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = circle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
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

TEST_F(CirclePolymorphismTest, TestCreateDfsIteratorShouldIsDone) {
  Iterator* dfs_iter = circle_.createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

TEST_F(CirclePolymorphismTest, TestCreateBfsIteratorShouldIsDone) {
  Iterator* bfs_iter = circle_.createBFSIterator();

  ASSERT_TRUE(bfs_iter->isDone());

  delete bfs_iter;
}

TEST_F(CirclePolymorphismTest, TestCreateListIteratorShouldIsDone) {
  Iterator* list_iter = circle_.createListIterator();

  ASSERT_TRUE(list_iter->isDone());

  delete list_iter;
}
