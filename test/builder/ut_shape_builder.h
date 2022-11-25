#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "../../src/builder/shape_builder.h"
#include "../../src/circle.h"
#include "../../src/point.h"
#include "../../src/shape.h"

TEST(ShapeBuilderTest, TestBuildCircle) {
  auto builder = ShapeBuilder{};
  const auto center = Point{1, 2};
  const auto on_circle = Point{-2, 6};

  builder.buildCircle(&center, &on_circle);

  std::vector<Shape*> shapes = builder.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* circle = shapes.at(0);
  ASSERT_NEAR(31.415, circle->perimeter(), 0.001);
  ASSERT_NEAR(78.539, circle->area(), 0.001);

  for (auto&& s : shapes) {
    delete s;
  }
}

TEST(ShapeBuilderTest, TestBuildTriangle) {
  auto builder = ShapeBuilder{};
  const auto vertices =
      std::array<Point, 3>{Point{0, 0}, Point{3, 0}, Point{0, 4}};

  builder.buildTriangle(&vertices.at(0), &vertices.at(1), &vertices.at(2));

  std::vector<Shape*> shapes = builder.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* triangle = shapes.at(0);
  /* Since the order of inner vectors aren't defined,
    we can't test with info. */
  ASSERT_EQ(12, triangle->perimeter());
  ASSERT_EQ(6, triangle->area());

  for (auto&& s : shapes) {
    delete s;
  }
}
