#include <gtest/gtest.h>

#include <set>

#include "../../src/circle.h"
#include "../../src/graphics/drawing.h"
#include "../../src/graphics/real_canvas.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/point.h"
#include "../../src/triangle.h"
#include "mock_sdl_renderer.h"

class RealCanvasTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  Drawing drawing_{{new Circle{{{1, 2}, {4, 6}}},
                    new Triangle{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}}}};
  MockSDLRenderer mock_sdl_renderer_{};
  SDLAdapter canvas_{1024, 768, &mock_sdl_renderer_};
};

TEST_F(RealCanvasTest, UpdateShouldDrawAllShapes) {
  auto real_canvas = RealCanvas{&canvas_, &drawing_};

  real_canvas.update();

  { /* circle should be drawn */
    const double* args = mock_sdl_renderer_.renderDrawCircleCalledArgs();
    ASSERT_NEAR(1, args[0], DELTA);
    ASSERT_NEAR(2, args[1], DELTA);
    ASSERT_NEAR(5, args[2], DELTA);
  }
  { /* triangle should be drawn */
    const auto expected_points = std::set<Point>{{0, 0}, {3, 0}, {3, 4}};
    const int size = mock_sdl_renderer_.renderDrawLinesCalledSize();
    ASSERT_EQ(expected_points.size() * 2, size);
    const double* x_and_ys = mock_sdl_renderer_.renderDrawLinesCalledPoints();
    for (int i = 0; i < size; i += 2) {
      /* order is irrelevant */
      ASSERT_TRUE(expected_points.find(Point{x_and_ys[i], x_and_ys[i + 1]}) !=
                  expected_points.end());
    }
    delete[] x_and_ys; /* the mocking class takes the ownership, while the real
                          class doesn't */
  }
}
