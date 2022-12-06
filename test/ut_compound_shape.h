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
 protected:
  const double DELTA = 0.001;

  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
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
  auto circle = Circle{{{1, 2}, {0, 0}}};

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
  const std::set<const Point*> vertices = level_one_compound_.getPoints();

  /* the key comparison used by set are the memory positions.
   * Our comparison can't relay on that since we don't know where the points
   * should be. A workaround is to traverse the set and dump the points
   * into another set which compares with value. */
  const auto vertices_with_value_as_compare =
      std::set<const Point*, std::function<bool(const Point*, const Point*)>>{
          vertices.begin(), vertices.end(),
          [](const Point* p1, const Point* p2) {
            return p1->info() < p2->info();
          }};
  const auto expected_vertices = std::vector<Point>{
      {6, 7}, {-4, -3},                 /* circle */
      {0, 0}, {3, 0},   {0, 4}, {3, 4}, /* rectangle */
      {0, 0}, {3, 0},   {3, 4},         /* triangle */
  };
  ASSERT_EQ(6, vertices.size()); /* no duplicates */
  for (const Point& vertex : expected_vertices) {
    ASSERT_TRUE(vertices_with_value_as_compare.find(&vertex) !=
                vertices_with_value_as_compare.end());
  }
  for (const Point* p : vertices) {
    delete p;
  }
}

TEST_F(CompoundShapeDepthTwoTest, ReplaceShouldReplaceTheShape) {
  level_one_compound_.replace(&circle_, &triangle_);

  const std::string actual = level_one_compound_.info();
  /* clang-format off */
  const std::string expected =
      "CompoundShape ("
        "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        ")"
      ")";
  /* clang-format on */
  ASSERT_EQ(expected, actual);
}
