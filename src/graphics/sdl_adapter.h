#ifndef SRC_GRAPHICS_SDL_ADAPTER_H_
#define SRC_GRAPHICS_SDL_ADAPTER_H_

#include <set>

#include "../circle.h"
#include "../point.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "canvas.h"
#include "sdl/sdl.h"

class SDLAdapter : public Canvas {
 public:
  SDLAdapter(const int width, const int height, SDL* const sdl) : sdl_{sdl} {
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
    // delete[] x_and_ys;
  }

  void drawRectangle(const Rectangle* rect) const override {}
  void display() {}

 private:
  SDL* sdl_;
};

#endif /* end of include guard: SRC_GRAPHICS_SDL_ADAPTER_H_ */
