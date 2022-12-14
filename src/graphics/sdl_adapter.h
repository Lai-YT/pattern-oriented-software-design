#ifndef SRC_GRAPHICS_SDL_ADAPTER_H_
#define SRC_GRAPHICS_SDL_ADAPTER_H_

#include <set>
#include <stdexcept>
#include <vector>

#include "../circle.h"
#include "../point.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "canvas.h"
#include "sdl/sdl.h"

class SDLAdapter : public Canvas {
 public:
  SDLAdapter(const int width, const int height, SDL* const sdl) : sdl_{sdl} {
    if (width <= 0 || height <= 0) {
      throw NonPositiveLengthOfSideException{"both sides should >= 0"};
    }
    sdl_->init(width, height);
  }

  void drawCircle(const Circle* cir) const override {
    const std::set<Point> points = cir->getPoints();
    double x = 0;
    double y = 0;
    for (const Point& p : points) {
      x += p.x();
      y += p.y();
    }
    sdl_->renderDrawCircle(x / points.size(), y / points.size(), cir->radius());
  }

  void drawTriangle(const Triangle* tri) const override {
    const std::set<Point> points = tri->getPoints();
    double* x_and_ys = new double[points.size() * 2];
    int i = 0;
    for (const Point& p : points) {
      x_and_ys[i++] = p.x();
      x_and_ys[i++] = p.y();
    }
    sdl_->renderDrawLines(x_and_ys, points.size() * 2);
  }

  void drawRectangle(const Rectangle* rect) const override {
    /*
     * The order of points passed to renderDrawLines is important, the lines
     * should not be drawn on the diagonals but the sides.
     * The order is restricted to start from the smaller (<) with the last two
     * swapped.
     */

    const std::set<Point> points = rect->getPoints();
    auto ordered_points = std::vector<Point>{points.begin(), points.end()};
    std::swap(ordered_points.at(2), ordered_points.at(3));

    /* flatten into c array */
    double* x_and_ys = new double[points.size() * 2];
    int i = 0;
    for (const Point& p : ordered_points) {
      x_and_ys[i++] = p.x();
      x_and_ys[i++] = p.y();
    }
    sdl_->renderDrawLines(x_and_ys, points.size() * 2);
  }

  void display() override {
    sdl_->renderPresent();
  }

  class NonPositiveLengthOfSideException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

 private:
  SDL* sdl_;
};

#endif /* end of include guard: SRC_GRAPHICS_SDL_ADAPTER_H_ */
