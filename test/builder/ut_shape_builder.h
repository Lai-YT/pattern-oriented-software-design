#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "../../src/builder/shape_builder.h"
#include "../../src/circle.h"
#include "../../src/point.h"
#include "../../src/shape.h"

class ShapeBuilderTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  ShapeBuilder builder_{};

  void Delete_(const std::vector<Shape*> shapes) const {
    for (auto&& s : shapes) {
      delete s;
    }
  }
};

TEST_F(ShapeBuilderTest, TestBuildCircle) {
  builder_.buildCircle(Point{1, 2}, Point{-2, 6});

  std::vector<Shape*> shapes = builder_.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* circle = shapes.at(0);
  ASSERT_NEAR(31.415, circle->perimeter(), DELTA);
  ASSERT_NEAR(78.539, circle->area(), DELTA);

  Delete_(shapes);
}

TEST_F(ShapeBuilderTest, TestBuildTriangle) {
  builder_.buildTriangle(Point{0, 0}, Point{3, 0}, Point{0, 4});

  std::vector<Shape*> shapes = builder_.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* triangle = shapes.at(0);
  /* Since the order of inner vectors aren't defined,
    we can't test with info. */
  ASSERT_NEAR(12, triangle->perimeter(), DELTA);
  ASSERT_NEAR(6, triangle->area(), DELTA);

  Delete_(shapes);
}

TEST_F(ShapeBuilderTest, TestBuildRectangle) {
  builder_.buildRectangle(Point{0, 0}, Point{3, 0}, Point{0, 4});

  std::vector<Shape*> shapes = builder_.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* rectangle = shapes.at(0);
  ASSERT_NEAR(14, rectangle->perimeter(), DELTA);
  ASSERT_NEAR(12, rectangle->area(), DELTA);

  Delete_(shapes);
}

/* Builds a one-level compound shape which has 3 inner shape: a circle, a
 * triangle and a rectangle. */
TEST_F(ShapeBuilderTest, TestBuildCompoundShapeOfOneLevel) {
  /*
   * CompoundShape (
   *  Circle ()
   *  Triangle ()
   *  Rectangle ()
   * )
   */
  builder_.buildCompoundShape();
  builder_.buildCircle(Point{1, 2}, Point{-2, 6});
  builder_.buildTriangle(Point{0, 0}, Point{3, 0}, Point{0, 4});
  builder_.buildRectangle(Point{0, 0}, Point{3, 0}, Point{0, 4});
  builder_.buildCompoundEnd();

  std::vector<Shape*> shapes = builder_.getResult();
  ASSERT_EQ(1, shapes.size());
  Shape* compound = shapes.at(0);
  ASSERT_NEAR(31.415 + 12 + 14, compound->perimeter(), DELTA);
  ASSERT_NEAR(78.539 + 6 + 12, compound->area(), DELTA);

  Delete_(shapes);
}

TEST_F(ShapeBuilderTest, TestBuildCompoundShapeOfTwoLevelAndNonCompoundShapes) {
  /*
   * Circle ()
   * CompoundShape (
   *  CompoundShape (
   *   Triangle ()
   *   Circle ()
   *  )
   * )
   * Rectangle ()
   */
  builder_.buildCircle(Point{1, 2}, Point{-2, 6});
  builder_.buildCompoundShape();
  builder_.buildTriangle(Point{0, 0}, Point{3, 0}, Point{0, 4});
  builder_.buildCircle(Point{1, 2}, Point{-2, 6});
  builder_.buildCompoundEnd();
  builder_.buildRectangle(Point{0, 0}, Point{3, 0}, Point{0, 4});

  std::vector<Shape*> shapes = builder_.getResult();
  ASSERT_EQ(3, shapes.size());
  Shape* circle = shapes.at(0);
  EXPECT_NEAR(31.415, circle->perimeter(), DELTA);
  EXPECT_NEAR(78.539, circle->area(), DELTA);
  Shape* compound = shapes.at(1);
  EXPECT_NEAR(12 + 31.415, compound->perimeter(), DELTA);
  EXPECT_NEAR(6 + 78.539, compound->area(), DELTA);
  Shape* rectangle = shapes.at(2);
  EXPECT_NEAR(14, rectangle->perimeter(), DELTA);
  EXPECT_NEAR(12, rectangle->area(), DELTA);

  Delete_(shapes);
}
