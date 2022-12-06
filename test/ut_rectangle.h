#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "../src/iterator/factory/iterator_factory.h"
#include "../src/iterator/iterator.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/two_dimensional_vector.h"

class RectangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
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

TEST_F(RectangleTest, PassingNonOrthogonalSidesShouldThrowException) {
  const auto vector_1 = TwoDimensionalVector{{0, 0}, {3, 1}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {0, 4}};

  ASSERT_THROW({ const auto rectangle = Rectangle(vector_1, vector_2); },
               Rectangle::NonOrthogonalSideException);
}

TEST_F(RectangleTest, PassingSidesWithNoCommonPointShouldThrowException) {
  const auto vector_1 = TwoDimensionalVector{{1, 0}, {3, 0}};
  const auto vector_2 = TwoDimensionalVector{{0, 0}, {0, 4}};

  ASSERT_THROW({ const auto rectangle = Rectangle(&vector_1, &vector_2); },
               Rectangle::NoCommonPointException);
}

TEST_F(RectangleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.addShape(&rectangle_); },
               Shape::ShapeInaddibleException);
}

TEST_F(RectangleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.deleteShape(&rectangle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(RectangleTest, GetPointsShouldReturnTheFourVertices) {
  const auto expected_vertices_carried_by_vector =
      std::vector<Point>{{0, 0}, {3, 0}, {0, 4}};
  const auto expected_derived_vertex = Point{3, 4};

  const std::set<Point> vertices = rectangle_.getPoints();

  ASSERT_EQ(4, vertices.size());
  for (const Point& vertex : expected_vertices_carried_by_vector) {
    ASSERT_TRUE(vertices.find(vertex) != vertices.end());
  }
  ASSERT_TRUE(vertices.find(expected_derived_vertex) != vertices.end());
}

TEST_F(RectangleTest, GetPointsFromRotatedShouldReturnTheFourVertices) {
  const Rectangle rectangle_{{{4, 0}, {0, 3}}, {{7, 4}, {4, 0}}};
  const auto expected_vertices_carried_by_vector =
      std::vector<Point>{{4, 0}, {0, 3}, {7, 4}};
  const auto expected_derived_vertex = Point{3, 7};

  const std::set<Point> vertices = rectangle_.getPoints();

  ASSERT_EQ(4, vertices.size());
  for (const Point& vertex : expected_vertices_carried_by_vector) {
    ASSERT_TRUE(vertices.find(vertex) != vertices.end());
  }
  ASSERT_TRUE(vertices.find(expected_derived_vertex) != vertices.end());
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

TEST_F(RectanglePolymorphismTest,
       CreateIteratorWithBfsIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("BFS");

  Iterator* it = rectangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectanglePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("DFS");

  Iterator* it = rectangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectanglePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const IteratorFactory* factory = IteratorFactory::getInstance("List");

  Iterator* it = rectangle_.createIterator(factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
