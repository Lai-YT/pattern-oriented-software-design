#include <gtest/gtest.h>

#include <functional>
#include <set>
#include <vector>

#include "../src/iterator/factory/iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class TriangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
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

TEST_F(TriangleTest, PassingVectorsWithNoCommonPointShouldThrowException) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 0}};
  const auto vector_2 = TwoDimensionalVector{{3, 4}, {3, 0}};

  ASSERT_THROW({ const auto triangle = Triangle(&vector_1, &vector_2); },
               Triangle::NoCommonPointException);
}

TEST_F(TriangleTest, PassingParallelVectorsShouldThrowException) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {4, 0}};
  const auto vector_2 = TwoDimensionalVector{{4, 0}, {5, 0}};

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

TEST_F(TriangleTest, GetPointsShouldReturnTheThreeVertices) {
  const std::set<Point> vertices = triangle_.getPointsXX();
  const auto expected_vertices = std::vector<Point>{{0, 0}, {3, 0}, {3, 4}};

  ASSERT_EQ(3, vertices.size());
  for (const Point& vertex : expected_vertices) {
    ASSERT_TRUE(vertices.find(vertex) != vertices.end());
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
  const IteratorFactory* factory = IteratorFactory::getInstance("BFS");

  Iterator* it = triangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TrianglePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("DFS");

  Iterator* it = triangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(TrianglePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("List");

  Iterator* it = triangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
