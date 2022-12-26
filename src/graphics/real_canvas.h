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
    auto printer = ShapePrinter{canvas_};
    std::vector<Shape*> shapes_to_draw = drawing_->shapes();
    for (auto* shape : shapes_to_draw) {
      shape->accept(&printer);
      for (auto it = std::unique_ptr<Iterator>{shape->createIterator(
               IteratorFactory::getInstance("DFS"))};
           !it->isDone(); it->next()) {
        it->currentItem()->accept(&printer);
      }
    }
  }

  RealCanvas(Canvas* canvas, Drawing* drawing)
      : canvas_{canvas}, drawing_{drawing} {
    drawing_->attach(this);
  }

 private:
  Canvas* canvas_;
  Drawing* drawing_;
};

#endif /* end of include guard: SRC_GRAPHICS_REAL_CANVAS_H_ */