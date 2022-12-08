#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/graphics/canvas.h"
#include "../../src/graphics/sdl/sdl.h"
#include "../../src/graphics/sdl_adapter.h"
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

TEST(SDLAdapterTest, RenderDrawCircleShouldBeCalledWithCorrectCentreAndRadius) {
  const auto circle = Circle{{{1, 2}, {4, 6}}};
  auto mockSDLRenderer = MockSDLRenderer{};
  auto canvas = SDLAdapter{1024, 768, &mockSDLRenderer};

  canvas.drawCircle(&circle);

  const double* args = mockSDLRenderer.renderDrawCircleCalledArgs();
  EXPECT_NEAR(1, args[0], 0.001);
  EXPECT_NEAR(2, args[1], 0.001);
  EXPECT_NEAR(5, args[2], 0.001);
}
