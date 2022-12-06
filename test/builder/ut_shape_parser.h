#include <gtest/gtest.h>

#include <memory>

#include "../../src/builder/shape_parser.h"
#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/factory/iterator_factory.h"
#include "../../src/iterator/iterator.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"

class ShapeParserTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  void Delete_(const std::vector<Shape*> shapes) const {
    for (auto&& s : shapes) {
      delete s;
    }
  }
};

TEST_F(ShapeParserTest, TestParseCircle) {
  const auto input = std::string{"Circle (Vector ((3, 4), (0, 8)))"};
  ShapeParser parser{input};

  parser.parse();

  std::vector<Shape*> shapes = parser.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* circle = shapes.at(0);
  ASSERT_NEAR(31.415, circle->perimeter(), DELTA);
  ASSERT_NEAR(78.539, circle->area(), DELTA);

  Delete_(shapes);
}

TEST_F(ShapeParserTest, TestParseTriangle) {
  const auto input = std::string{
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))"};
  ShapeParser parser{input};

  parser.parse();

  std::vector<Shape*> shapes = parser.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* triangle = shapes.at(0);
  ASSERT_NEAR(12, triangle->perimeter(), DELTA);
  ASSERT_NEAR(6, triangle->area(), DELTA);

  Delete_(shapes);
}

TEST_F(ShapeParserTest, TestParseRectangle) {
  const auto input = std::string{
      "Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, "
      "14.00), (15.00, 10.00)))"};
  ShapeParser parser{input};

  parser.parse();

  std::vector<Shape*> shapes = parser.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* rectangle = shapes.at(0);
  ASSERT_NEAR(16.492, rectangle->perimeter(), DELTA);
  ASSERT_NEAR(17, rectangle->area(), DELTA);

  Delete_(shapes);
}

/* A complex test that uses Iterator to traverse the CompoundShape. */
TEST_F(ShapeParserTest, TestParseTwoLevelCompoundShape) {
  /* clang-format off */
  const std::string input =
      "CompoundShape ("
        "Circle (Vector ((1.00, 2.00), (-3.00, 5.00))), "
        "CompoundShape ("
          "Rectangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((0.00, 0.00), (0.00, 4.00))), "
          "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
        "),"
        "Rectangle (Vector ((0.00, 0.00), (6.00, 0.00)), Vector ((0.00, 0.00), (0.00, 8.00)))"
      ")";
  /* clang-format on */
  ShapeParser parser{input};

  parser.parse();

  std::vector<Shape*> shapes = parser.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* level_one_compound = shapes.at(0);
  auto dfs_itr = std::unique_ptr<Iterator>{
      level_one_compound->createIterator(IteratorFactory::getInstance("DFS"))};
  {
    Shape* circle = dynamic_cast<Circle*>(dfs_itr->currentItem());
    ASSERT_TRUE(circle);
    ASSERT_NEAR(31.415, circle->perimeter(), DELTA);
    ASSERT_NEAR(78.539, circle->area(), DELTA);
  }
  dfs_itr->next();
  {
    Shape* compound = dynamic_cast<CompoundShape*>(dfs_itr->currentItem());
    ASSERT_TRUE(compound);
    ASSERT_NEAR(14 + 12, compound->perimeter(), DELTA);
    ASSERT_NEAR(12 + 6, compound->area(), DELTA);
  }
  dfs_itr->next();
  {
    Shape* rectangle = dynamic_cast<Rectangle*>(dfs_itr->currentItem());
    ASSERT_TRUE(rectangle);
    ASSERT_NEAR(14, rectangle->perimeter(), DELTA);
    ASSERT_NEAR(12, rectangle->area(), DELTA);
  }
  dfs_itr->next();
  {
    Shape* triangle = dynamic_cast<Triangle*>(dfs_itr->currentItem());
    ASSERT_TRUE(triangle);
    ASSERT_NEAR(12, triangle->perimeter(), DELTA);
    ASSERT_NEAR(6, triangle->area(), DELTA);
  }
  dfs_itr->next();
  {
    Shape* rectangle = dynamic_cast<Rectangle*>(dfs_itr->currentItem());
    ASSERT_TRUE(rectangle);
    ASSERT_NEAR(28, rectangle->perimeter(), DELTA);
    ASSERT_NEAR(48, rectangle->area(), DELTA);
  }
  dfs_itr->next();
  ASSERT_TRUE(dfs_itr->isDone());

  Delete_(shapes);
}
