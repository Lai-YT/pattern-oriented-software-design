#ifndef SRC_GRAPHICS_REAL_CANVAS_H_
#define SRC_GRAPHICS_REAL_CANVAS_H_

#include <memory>
#include <vector>

#include "../iterator/factory/iterator_factory.h"
#include "../iterator/iterator.h"
#include "../shape.h"
#include "../visitor/shape_printer.h"
#include "canvas.h"
#include "drawing.h"
#include "observer/observer.h"

class RealCanvas : public Observer {
 public:
  /** @brief Redraws all shapes. */
  void update() override {
    for (auto* shape : drawing_->shapes()) {
      shape->accept(&printer_);
      DrawInnerShapesInDepthFirstOrder_(shape);
    }
  }

  RealCanvas(Canvas* canvas, Drawing* drawing)
      : canvas_{canvas}, drawing_{drawing}, printer_{canvas} {
    drawing_->attach(this);
  }

 private:
  Canvas* canvas_;
  Drawing* drawing_;
  ShapePrinter printer_;

  /**
   * @note The root shape won't be drawn and passing a non-compound shape is
   * safe.
   */
  void DrawInnerShapesInDepthFirstOrder_(Shape* shape) {
    for (auto it = std::unique_ptr<Iterator>{shape->createIterator(
             IteratorFactory::getInstance("DFS"))};
         !it->isDone(); it->next()) {
      it->currentItem()->accept(&printer_);
    }
  }
};

#endif /* end of include guard: SRC_GRAPHICS_REAL_CANVAS_H_ */