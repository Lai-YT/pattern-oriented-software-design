#include <gtest/gtest.h>

#include <array>
#include <set>

#include "../../src/circle.h"
#include "../../src/graphics/canvas.h"
#include "../../src/graphics/sdl/sdl.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/rectangle.h"
#include "../../src/triangle.h"
#include "mock_sdl_renderer.h"

class SDLAdapterTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  MockSDLRenderer mock_sdl_renderer_{};
  SDLAdapter canvas_{1024, 768, &mock_sdl_renderer_};
};

TEST_F(SDLAdapterTest, InitShouldBeCalled) {
  ASSERT_TRUE(mock_sdl_renderer_.isInitCalled());
}

TEST_F(SDLAdapterTest, InitShouldBeCalledWithCorrectWidthAndHeight) {
  ASSERT_EQ(1024, mock_sdl_renderer_.initWidth());
  ASSERT_EQ(768, mock_sdl_renderer_.initHeight());
}

TEST_F(SDLAdapterTest, InitWithNonPositiveWidthShouldThrowException) {
  const int non_positive_width = 0;

  ASSERT_THROW(SDLAdapter(non_positive_width, 768, &mock_sdl_renderer_),
               SDLAdapter::NonPositiveLengthOfSideException);
}

TEST_F(SDLAdapterTest, InitWithNonPositiveHeightShouldThrowException) {
  const int non_positive_height = 0;

  ASSERT_THROW(SDLAdapter(1024, non_positive_height, &mock_sdl_renderer_),
               SDLAdapter::NonPositiveLengthOfSideException);
}
TEST_F(SDLAdapterTest,
       DrawCircleShouldCallRenderDrawCircleWithCorrectCentreAndRadius) {
  const auto circle = Circle{{{1, 2}, {4, 6}}};

  canvas_.drawCircle(&circle);

  const double* args = mock_sdl_renderer_.renderDrawCircleCalledArgs();
  EXPECT_NEAR(1, args[0], DELTA);
  EXPECT_NEAR(2, args[1], DELTA);
  EXPECT_NEAR(5, args[2], DELTA);
}

TEST_F(SDLAdapterTest, DrawTriangleShouldCallRenderDrawLinesWithCorrectPoints) {
  const auto triangle = Triangle{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  const auto expected_points = std::set<Point>{{0, 0}, {3, 0}, {3, 4}};

  canvas_.drawTriangle(&triangle);

  /* XXX: the mocking class takes the ownership, while the real class doesn't.
   */
  const int size = mock_sdl_renderer_.renderDrawLinesCalledSize();
  ASSERT_EQ(expected_points.size() * 2, size);
  const double* x_and_ys = mock_sdl_renderer_.renderDrawLinesCalledPoints();
  for (int i = 0; i < size; i += 2) {
    /* order is irrelevant */
    ASSERT_TRUE(expected_points.find(Point{x_and_ys[i], x_and_ys[i + 1]}) !=
                expected_points.end());
  }
  delete[] x_and_ys;
}

TEST_F(SDLAdapterTest,
       DrawRectangleShouldCallRenderDrawLinesWithCorrectOrderedPoints) {
  const auto rectangle = Rectangle{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  /* The order is important, the lines should not be drawn on the diagonals but
    the sides. The order is restricted to start from the smaller (<) with the
    last two swapped. */
  const auto expected_points = std::array<const Point, 4>{
      Point{0, 0}, Point{0, 4}, Point{3, 4}, Point{3, 0}};

  canvas_.drawRectangle(&rectangle);

  /* XXX: the mocking class takes the ownership, while the real class doesn't.
   */
  const int size = mock_sdl_renderer_.renderDrawLinesCalledSize();
  ASSERT_EQ(expected_points.size() * 2, size);
  const double* x_and_ys = mock_sdl_renderer_.renderDrawLinesCalledPoints();
  int i = 0;
  for (const Point& expect : expected_points) {
    const auto actual = Point{x_and_ys[i++], x_and_ys[i++]};
    EXPECT_EQ(expect, actual)
        << "Expect:\n\t" << expect.info() << "\nActual:\n\t" << actual.info();
  }
  delete[] x_and_ys;
}

TEST_F(SDLAdapterTest, DisplayShouldCallRenderPresent) {
  canvas_.display();

  ASSERT_TRUE(mock_sdl_renderer_.isRenderPresentCalled());
}
