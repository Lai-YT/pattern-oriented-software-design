#include <gtest/gtest.h>

#include <vector>

#include "../../src/builder/shape_builder.h"
#include "../../src/circle.h"
#include "../../src/point.h"
#include "../../src/shape.h"

TEST(ShapeBuilderTest, TestBuildCircle) {
  auto builder = ShapeBuilder{};
  const auto center = Point(1, 2);
  const auto on_circle = Point(-2, 6);

  builder.buildCircle(&center, &on_circle);

  std::vector<Shape*> shapes = builder.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* circle = shapes.at(0);
  ASSERT_EQ("Circle (Vector ((1.00, 2.00), (-2.00, 6.00)))", circle->info());

  for (auto&& s : shapes) {
    delete s;
  }
}
