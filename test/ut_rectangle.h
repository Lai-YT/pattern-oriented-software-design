#include <gtest/gtest.h>

#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/list_iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

class RectangleTest : public ::testing::Test {
 private:
  const Point vector_head_1_ = Point{0, 0};
  const Point vector_tail_1_ = Point{3, 0};
  const TwoDimensionalVector vector_1_{&vector_head_1_, &vector_tail_1_};
  const Point vector_head_2_ = Point{0, 0};
  const Point vector_tail_2_ = Point{0, 4};
  const TwoDimensionalVector vector_2_{&vector_head_2_, &vector_tail_2_};

 protected:
  const double DELTA = 0.001;

  Rectangle rectangle_{&vector_1_, &vector_2_};
};

TEST_F(RectangleTest, TestLength) {
  ASSERT_NEAR(3, rectangle_.length(), DELTA);
}

TEST_F(RectangleTest, TestWidth) {
  ASSERT_NEAR(4, rectangle_.width(), DELTA);
}

TEST_F(RectangleTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_.info());
}

TEST_F(RectangleTest, TestArea) {
  ASSERT_NEAR(12, rectangle_.area(), DELTA);
}

TEST_F(RectangleTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_.perimeter(), DELTA);
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
  Iterator* dfs_iter = rectangle_.createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

TEST_F(RectangleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.addShape(&rectangle_); },
               Shape::ShapeInaddibleException);
}

TEST_F(RectangleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.deleteShape(&rectangle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(RectangleTest,
       CreateIteratorWithBfsIteratorFactoryShouldGetNullIterator) {
  const auto factory = BFSIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectangleTest,
       CreateIteratorWithDfsIteratorFactoryShouldGetNullIterator) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectangleTest,
       CreateIteratorWithListIteratorFactoryShouldGetNullIterator) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

class RectanglePolymorphismTest : public RectangleTest {
 protected:
  Shape& rectangle_{RectangleTest::rectangle_};
};

TEST_F(RectanglePolymorphismTest, TestInfo) {
  ASSERT_EQ(
      "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), "
      "(0.00, 4.00)))",
      rectangle_.info());
}

TEST_F(RectanglePolymorphismTest, TestArea) {
  ASSERT_NEAR(12, rectangle_.area(), DELTA);
}

TEST_F(RectanglePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(14, rectangle_.perimeter(), DELTA);
}

TEST_F(RectanglePolymorphismTest, TestCreateDfsIteratorShoudIsDone) {
  Iterator* dfs_iter = rectangle_.createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

TEST_F(RectanglePolymorphismTest, TestCreateBfsIteratorShoudIsDone) {
  Iterator* bfs_iter = rectangle_.createBFSIterator();

  ASSERT_TRUE(bfs_iter->isDone());

  delete bfs_iter;
}

TEST_F(RectanglePolymorphismTest, TestCreateListIteratorShoudIsDone) {
  Iterator* list_iter = rectangle_.createListIterator();

  ASSERT_TRUE(list_iter->isDone());

  delete list_iter;
}
