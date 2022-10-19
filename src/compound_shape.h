#ifndef SRC_COMPOUND_SHAPE_H_
#define SRC_COMPOUND_SHAPE_H_

#include <algorithm>
#include <list>
#include <string>
#include <vector>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "shape.h"

class CompoundShape : public Shape {
 public:
  CompoundShape(const std::list<Shape*>& shapes)
      : shapes_{shapes.begin(), shapes.end()} {}

  CompoundShape(Shape** /* const here makes all shapes in shapes_ point to
                                 the first shape */
                    shapes,
                const size_t size)
      : shapes_{shapes, shapes + size} {}

  double area() const override {
    double result = 0;
    for (const auto& shape : shapes_) {
      result += shape->area();
    }
    return result;
  }

  double perimeter() const override {
    double result = 0;
    for (const auto& shape : shapes_) {
      result += shape->perimeter();
    }
    return result;
  }

  std::string info() const override {
    auto inner_info = std::string{};
    if (!shapes_.empty()) {
      for (const auto& shape : shapes_) {
        inner_info += shape->info() + ", ";
      }
      /* remove the last ", " */
      inner_info.pop_back();
      inner_info.pop_back();
    }
    return "CompoundShape (" + inner_info + ")";
  }

  Iterator* createIterator(const IteratorFactory* const factory) const {
    return factory->createIterator(shapes_.begin(), shapes_.end());
  }

  void addShape(Shape* const shape) override {
    shapes_.push_back(shape);
  }

  /** If target appears multiple times, they are all deleted. */
  void deleteShape(Shape* target) override {
    /* from level one */
    shapes_.remove(target);
    /* recursively from all levels */
    for (auto* s : shapes_) {
      try {
        s->deleteShape(target);
      } catch (const Shape::ShapeUndeletableException& e) {
        /* slient exception,
         * resemble `rm -f`, which ignores the non-existing error */
      }
    }
  }

 private:
  std::list<Shape*> shapes_;
};

#endif /* end of include guard: SRC_COMPOUND_SHAPE_H_ */
