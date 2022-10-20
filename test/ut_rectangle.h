#include <gtest/gtest.h>

#include <functional>
#include <set>
#include <vector>

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

TEST_F(RectangleTest, AddShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.addShape(&rectangle_); },
               Shape::ShapeInaddibleException);
}

TEST_F(RectangleTest, DeleteShapeShouldThrowException) {
  ASSERT_THROW({ rectangle_.deleteShape(&rectangle_); },
               Shape::ShapeUndeletableException);
}

TEST_F(RectangleTest, GetPointsShouldReturnTheFourVertices) {
  const std::set<Point*> vertices = rectangle_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the points
   * into another set which compares with value. */
  const auto vertices_with_value_as_compare =
      std::set<Point*, std::function<bool(Point*, Point*)>>{
          vertices.begin(), vertices.end(),
          [](Point* p1, Point* p2) { return p1->info() < p2->info(); }};
  auto expected_vertices_carried_by_vector =
      std::vector<Point>{{0, 0}, {3, 0}, {0, 4}};
  auto expected_derived_vertex = Point{3, 4};
  ASSERT_EQ(4, vertices.size());
  for (Point& vertex : expected_vertices_carried_by_vector) {
    ASSERT_TRUE(vertices_with_value_as_compare.find(&vertex) !=
                vertices_with_value_as_compare.end());
  }
  ASSERT_TRUE(vertices_with_value_as_compare.find(&expected_derived_vertex) !=
              vertices_with_value_as_compare.end());
  for (Point* p : vertices) {
    delete p;
  }
}

TEST_F(RectangleTest, GetPointsFromRotatedShouldReturnTheFourVertices) {
  const Point vector_head_1 = Point{4, 0};
  const Point vector_tail_1 = Point{0, 3};
  const TwoDimensionalVector vector_1{&vector_head_1, &vector_tail_1};
  const Point vector_head_2 = Point{7, 4};
  const Point vector_tail_2 = Point{4, 0};
  const TwoDimensionalVector vector_2{&vector_head_2, &vector_tail_2};
  const Rectangle rectangle_{&vector_1, &vector_2};

  const std::set<Point*> vertices = rectangle_.getPoints();

  auto vertices_with_value_as_compare =
      std::set<Point*, std::function<bool(Point*, Point*)>>{
          vertices.begin(), vertices.end(),
          [](Point* p1, Point* p2) { return p1->info() < p2->info(); }};
  auto expected_vertices_carried_by_vector =
      std::vector<Point>{{4, 0}, {0, 3}, {7, 4}};
  auto expected_derived_vertex = Point{3, 7};
  ASSERT_EQ(4, vertices.size());
  for (Point& vertex : expected_vertices_carried_by_vector) {
    ASSERT_TRUE(vertices_with_value_as_compare.find(&vertex) !=
                vertices_with_value_as_compare.end());
  }
  ASSERT_TRUE(vertices_with_value_as_compare.find(&expected_derived_vertex) !=
              vertices_with_value_as_compare.end());
  for (Point* p : vertices) {
    delete p;
  }
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
  const auto factory = BFSIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectanglePolymorphismTest,
       CreateIteratorWithDfsIteratorFactoryShouldIsDone) {
  const auto factory = DFSIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}

TEST_F(RectanglePolymorphismTest,
       CreateIteratorWithListIteratorFactoryShouldIsDone) {
  const auto factory = ListIteratorFactory{};

  Iterator* it = rectangle_.createIterator(&factory);

  ASSERT_TRUE(it->isDone());

  delete it;
}
