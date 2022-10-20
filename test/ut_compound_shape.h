#include <gtest/gtest.h>

#include <set>
#include <string>
#include <vector>

#include "../src/circle.h"
#include "../src/compound_shape.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class CompoundShapeTest : public ::testing::Test {
 private:
  const Point circle_vector_head_{1, 2};
  const Point circle_vector_tail_{-3, 5};
  const TwoDimensionalVector circle_vector_{&circle_vector_head_,
                                            &circle_vector_tail_};
  const Point rectangle_vector_head_1_{0, 0};
  const Point rectangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector rectangle_vector_1{&rectangle_vector_head_1_,
                                                &rectangle_vector_tail_1_};
  const Point rectangle_vector_head_2_{0, 0};
  const Point rectangle_vector_tail_2_{0, 4};
  const TwoDimensionalVector rectangle_vector_2{&rectangle_vector_head_2_,
                                                &rectangle_vector_tail_2_};
  const Point triangle_vector_head_1_{0, 0};
  const Point triangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector triangle_vector_1_{&triangle_vector_head_1_,
                                                &triangle_vector_tail_1_};
  const Point triangle_vector_head_2_{3, 4};
  const Point triangle_vector_tail_2_{3, 0};
  const TwoDimensionalVector triangle_vector_2_{&triangle_vector_head_2_,
                                                &triangle_vector_tail_2_};

  /* protected after private because non-static data members are initialized in
   * order of declaration in the class definition. */
 protected:
  const double DELTA = 0.001;

  Circle circle_{&circle_vector_};
  Rectangle rectangle_{&rectangle_vector_1, &rectangle_vector_2};
  Triangle triangle_{&triangle_vector_1_, &triangle_vector_2_};
};

class CompoundShapeDepthOneTest : public CompoundShapeTest {
 protected:
  /*
   *     compound
   *     /   |   \
   *    cir  rec  tri
   */
  CompoundShape compound_{{&circle_, &rectangle_, &triangle_}};
};

class CompoundShapeDepthTwoTest : public CompoundShapeTest {
 protected:
  /*
   *     compound_1
   *      /    \
   *     /   compound_2
   *    /      /   \
   *  cir     rec  tri
   */
  CompoundShape level_two_compound_{{&rectangle_, &triangle_}};
  CompoundShape level_one_compound_{{&circle_, &level_two_compound_}};
};

TEST_F(CompoundShapeTest, TestConstructorTakingCStyleArrayShouldCompile) {
  Shape* shapes[] = {&circle_, &rectangle_, &triangle_};
  const auto compound = CompoundShape{shapes, 3};
}

TEST_F(CompoundShapeTest, TestInfoOfEmptyCompoundShape) {
  auto compound = CompoundShape{{}};

  const std::string actual = compound.info();

  const std::string expected = "CompoundShape ()";
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, TestArea) {
  const double actual = compound_.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthTwoTest, TestArea) {
  const double actual = level_one_compound_.area();
  const double expected = 96.54;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthOneTest, TestPerimeter) {
  const double actual = compound_.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthTwoTest, TestPerimeter) {
  const double actual = level_one_compound_.perimeter();
  const double expected = 57.416;

  ASSERT_NEAR(expected, actual, DELTA);
}

TEST_F(CompoundShapeDepthOneTest, TestInfo) {
  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
      ")";
  /* clang-format on */

  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, TestAddShape) {
  compound_.addShape(&circle_);

  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00))), "
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, TestDeleteExistingShapeFromFront) {
  compound_.deleteShape(&triangle_);

  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, TestDeleteExistingShapeFromEnd) {
  compound_.deleteShape(&circle_);

  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, TestDeleteExistingShapeFromMiddle) {
  compound_.deleteShape(&rectangle_);

  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthOneTest, DeleteShapeNotExistShouldHaveNoEffect) {
  const auto vector_head = Point{1, 2};
  const auto vector_tail = Point{0, 0};
  const auto vector = TwoDimensionalVector{&vector_head, &vector_tail};
  auto circle = Circle{&vector};

  compound_.deleteShape(&circle);

  const std::string actual = compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestInfo) {
  const std::string actual = level_one_compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  /* clang-format on */

  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestAddShapeToEmptyCompoundShape) {
  auto compound = CompoundShape{{}};

  compound.addShape(&circle_);

  const std::string actual = compound.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestAddShape) {
  level_one_compound_.addShape(&circle_);

  const std::string actual = level_one_compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        "), "
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00)))" /* the shape being added */
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestDeleteShapeFromEmptyCompoundShape) {
  auto compound = CompoundShape{{}};

  compound.deleteShape(&circle_);

  const std::string actual = compound.info();
  const std::string expected = "CompoundShape ()";
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, TestDeleteShapeFromLowLevel) {
  level_one_compound_.deleteShape(&rectangle_);

  const std::string actual = level_one_compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest, DeleteShapeShouldDeleteAllTargetShapes) {
  auto level_one_compound =
      CompoundShape{{&circle_, &level_two_compound_, &circle_}};

  level_one_compound.deleteShape(&circle_);

  const std::string actual = level_one_compound.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}

TEST_F(CompoundShapeDepthTwoTest,
       GetPointsShouldReturnAllVerticesShapesThatContains) {
  const std::set<Point*> vertices = level_one_compound_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the points
   * into another set which compares with value. */
  const auto vertices_with_value_as_compare =
      std::set<Point*, std::function<bool(Point*, Point*)>>{
          vertices.begin(), vertices.end(),
          [](Point* p1, Point* p2) { return p1->info() < p2->info(); }};
  auto expected_vertices = std::vector<Point>{
      {6, 7}, {-4, -3},                 /* circle */
      {0, 0}, {3, 0},   {0, 4}, {3, 4}, /* rectangle */
      {0, 0}, {3, 0},   {3, 4},         /* triangle */
  };
  for (Point* vertex : vertices) {
    std::cout << vertex->info() << '\n';
  }
  ASSERT_EQ(6, vertices.size()); /* no duplicates */
  for (Point& vertex : expected_vertices) {
    ASSERT_TRUE(vertices_with_value_as_compare.find(&vertex) !=
                vertices_with_value_as_compare.end());
  }
  for (Point* p : vertices) {
    delete p;
  }
}
