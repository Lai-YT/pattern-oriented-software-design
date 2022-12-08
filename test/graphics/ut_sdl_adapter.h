#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/graphics/canvas.h"
#include "../../src/graphics/sdl/sdl.h"
#include "../../src/graphics/sdl_adapter.h"
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
  const int expected_size = 6;
  const double expected_points[expected_size] = {0, 0, 3, 0, 3, 4};

  canvas_.drawTriangle(&triangle);

  /* XXX: the mocking class takes the ownership, while the real class doesn't.
   */
  const int size = mock_sdl_renderer_.renderDrawLinesCalledSize();
  ASSERT_EQ(expected_size, size);
  const double* points = mock_sdl_renderer_.renderDrawLinesCalledPoints();
  for (int i = 0; i < size; i++) {
    ASSERT_NEAR(expected_points[i], points[i], DELTA);
  }
  delete[] points;
}
