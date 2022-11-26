#include <gtest/gtest.h>

#include "../../src/builder/shape_parser.h"
#include "../../src/shape.h"

class ShapeParserTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;
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

  for (auto&& s : shapes) {
    delete s;
  }
}
