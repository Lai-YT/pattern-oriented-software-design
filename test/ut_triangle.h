#include <gtest/gtest.h>

#include "../src/iterator/factory/bfs_iterator_factory.h"
#include "../src/iterator/factory/dfs_iterator_factory.h"
#include "../src/iterator/factory/list_iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class TriangleTest : public ::testing::Test {
 private:
  const Point vector_head_1_ = Point{0, 0};
  const Point vector_tail_1_ = Point{3, 0};
  const TwoDimensionalVector vector_1_{&vector_head_1_, &vector_tail_1_};
  const Point vector_head_2_ = Point{3, 4};
  const Point vector_tail_2_ = Point{3, 0};
  const TwoDimensionalVector vector_2_{&vector_head_2_, &vector_tail_2_};

 protected:
  const double DELTA = 0.001;

  Triangle triangle_{&vector_1_, &vector_2_};
};

TEST_F(TriangleTest, TestPerimeter) {
  ASSERT_NEAR(12, triangle_.perimeter(), DELTA);
}

TEST_F(TriangleTest, TestArea) {
  ASSERT_NEAR(6, triangle_.area(), DELTA);
}

TEST_F(TriangleTest, TestInfo) {
  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      triangle_.info());
}

TEST_F(TriangleTest, PassingVectorsWithNoCommonPointShoudThrowException) {
  const auto vector_head_1 = Point{0, 0};
  const auto vector_tail_1 = Point{4, 0};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{3, 4};
  const auto vector_tail_2 = Point{3, 0};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto triangle = Triangle(&vector_1, &vector_2); },
               Triangle::NoCommonPointException);
}

TEST_F(TriangleTest, PassingParallelVectorsShoudThrowException) {
  const auto vector_head_1 = Point{0, 0};
  const auto vector_tail_1 = Point{4, 0};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{4, 0};
  const auto vector_tail_2 = Point{5, 0};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto triangle = Triangle(&vector_1, &vector_2); },
               Triangle::ParallelSideException);
}

TEST_F(TriangleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ triangle_.addShape(&triangle_); },
               Shape::ShapeInaddibleException);
}

TEST_F(TriangleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ triangle_.deleteShape(&triangle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(TriangleTest,
       CreateIteratorWithBfsIteratorFactoryShouldGetNullIterator) {
  const auto factory = BFSIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TriangleTest,
       CreateIteratorWithDfsIteratorFactoryShouldGetNullIterator) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TriangleTest,
       CreateIteratorWithListIteratorFactoryShouldGetNullIterator) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

class TrianglePolymorphismTest : public TriangleTest {
 protected:
  Shape& triangle_{TriangleTest::triangle_};
};

TEST_F(TrianglePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(12, triangle_.perimeter(), DELTA);
}

TEST_F(TrianglePolymorphismTest, TestArea) {
  ASSERT_NEAR(6, triangle_.area(), DELTA);
}

TEST_F(TrianglePolymorphismTest, TestInfo) {
  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      triangle_.info());
}

TEST_F(TrianglePolymorphismTest, TestCreateDfsIteratorShouldIsDone) {
  Iterator* dfs_iter = triangle_.createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

TEST_F(TrianglePolymorphismTest, TestCreateBfsIteratorShouldIsDone) {
  Iterator* bfs_iter = triangle_.createBFSIterator();

  ASSERT_TRUE(bfs_iter->isDone());

  delete bfs_iter;
}

TEST_F(TrianglePolymorphismTest, TestCreateListIteratorShouldIsDone) {
  Iterator* list_iter = triangle_.createListIterator();

  ASSERT_TRUE(list_iter->isDone());

  delete list_iter;
}
