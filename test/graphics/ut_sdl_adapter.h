#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/graphics/canvas.h"
#include "../../src/graphics/sdl/sdl.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/triangle.h"
#include "mock_sdl_renderer.h"

TEST(SDLAdapterTest, InitShouldBeCalled) {
  auto mockSDLRenderer = MockSDLRenderer{};

  auto canvas = SDLAdapter{1024, 768, &mockSDLRenderer};

  ASSERT_TRUE(mockSDLRenderer.isInitCalled());
}

TEST(SDLAdapterTest, InitShouldBeCalledWithCorrectWidthAndHeight) {
  const int width = 1024;
  const int height = 768;
  auto mockSDLRenderer = MockSDLRenderer{};

  auto canvas = SDLAdapter{width, height, &mockSDLRenderer};

  ASSERT_EQ(width, mockSDLRenderer.initWidth());
  ASSERT_EQ(height, mockSDLRenderer.initHeight());
}

TEST(SDLAdapterTest, InitWithNonPositiveWidthShouldThrowException) {
  const int non_positive_width = 0;
  auto mockSDLRenderer = MockSDLRenderer{};

  ASSERT_THROW(SDLAdapter(non_positive_width, 768, &mockSDLRenderer),
               SDLAdapter::NonPositiveLengthOfSideException);
}

TEST(SDLAdapterTest, InitWithNonPositiveHeightShouldThrowException) {
  const int non_positive_height = 0;
  auto mockSDLRenderer = MockSDLRenderer{};

  ASSERT_THROW(SDLAdapter(1024, non_positive_height, &mockSDLRenderer),
               SDLAdapter::NonPositiveLengthOfSideException);
}
TEST(SDLAdapterTest,
     DrawCircleShouldCallRenderDrawCircleWithCorrectCentreAndRadius) {
  const auto circle = Circle{{{1, 2}, {4, 6}}};
  auto mockSDLRenderer = MockSDLRenderer{};
  auto canvas = SDLAdapter{1024, 768, &mockSDLRenderer};

  canvas.drawCircle(&circle);

  const double* args = mockSDLRenderer.renderDrawCircleCalledArgs();
  EXPECT_NEAR(1, args[0], 0.001);
  EXPECT_NEAR(2, args[1], 0.001);
  EXPECT_NEAR(5, args[2], 0.001);
}

TEST(SDLAdapterTest, DrawTriangleShouldCallRenderDrawLinesWithCorrectPoints) {
  const auto triangle = Triangle{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  const int expected_size = 6;
  const double expected_points[expected_size] = {0, 0, 3, 0, 3, 4};
  auto mockSDLRenderer = MockSDLRenderer{};
  auto canvas = SDLAdapter{1024, 768, &mockSDLRenderer};

  canvas.drawTriangle(&triangle);

  /* XXX: the mocking class takes the ownership, while the real class doesn't.
   */
  const int size = mockSDLRenderer.renderDrawLinesCalledSize();
  ASSERT_EQ(expected_size, size);
  const double* points = mockSDLRenderer.renderDrawLinesCalledPoints();
  for (int i = 0; i < size; i++) {
    ASSERT_NEAR(expected_points[i], points[i], 0.001);
  }
  delete[] points;
}
