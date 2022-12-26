#ifndef SRC_GRAPHICS_REAL_CANVAS_H_
#define SRC_GRAPHICS_REAL_CANVAS_H_

#include "canvas.h"
#include "drawing.h"
#include "observer/observer.h"

class RealCanvas : public Observer {
 public:
  /** @brief Redraws all shapes. */
  void update() override {}

  RealCanvas(Canvas* canvas, Drawing* drawing) {}
};

#endif /* end of include guard: SRC_GRAPHICS_REAL_CANVAS_H_ */