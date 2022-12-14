#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_REFRESH_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_REFRESH_COMMAND_H_

#include <memory>
#include <vector>

#include "../../../iterator/factory/iterator_factory.h"
#include "../../../iterator/iterator.h"
#include "../../../shape.h"
#include "../../../visitor/shape_printer.h"
#include "../../canvas.h"
#include "command.h"

class RefreshCommand : public Command {
 public:
  RefreshCommand(Canvas* const canvas, const std::vector<Shape*>& shapes)
      : canvas_(canvas), shapes_(shapes), printer_{canvas_} {}

  void execute() override {
    for (auto* shape : shapes_) {
      ;
      shape->accept(&printer_);
      for (auto it = std::unique_ptr<Iterator>{shape->createIterator(
               IteratorFactory::getInstance("DFS"))};
           !it->isDone(); it->next()) {
        it->currentItem()->accept(&printer_);
      }
    }
  }

  void undo() override {}

 private:
  Canvas* canvas_;
  ShapePrinter printer_;
  std::vector<Shape*> shapes_;
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_REFRESH_COMMAND_H_ */
