#include <gtest/gtest.h>

#include <functional>
#include <set>
#include <vector>

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

TEST_F(TriangleTest, GetPointsShouldReturnTheThreeVerices) {
  const std::set<Point*> vertices = triangle_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the points
   * into another set which compares with value. */
  const auto vertices_with_value_as_compare =
      std::set<Point*, std::function<bool(Point*, Point*)>>{
          vertices.begin(), vertices.end(),
          [](Point* p1, Point* p2) { return p1->info() < p2->info(); }};
  auto expected_vertices = std::vector<Point>{{0, 0}, {3, 0}, {3, 4}};
  ASSERT_EQ(3, vertices.size());
  for (Point& vertex : expected_vertices) {
    ASSERT_TRUE(vertices_with_value_as_compare.find(&vertex) !=
                vertices_with_value_as_compare.end());
  }
  for (Point* p : vertices) {
    delete p;
  }
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

TEST_F(TrianglePolymorphismTest,
       CreateIteratorWithBfsIteratorFactoryShouldIsDone) {
  const auto factory = BFSIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TrianglePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TrianglePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = triangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
