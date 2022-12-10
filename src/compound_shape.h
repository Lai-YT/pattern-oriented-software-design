#ifndef SRC_COMPOUND_SHAPE_H_
#define SRC_COMPOUND_SHAPE_H_

#include <algorithm>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "point.h"
#include "shape.h"
#include "visitor/shape_visitor.h"

class CompoundShape : public Shape {
 public:
  CompoundShape(const std::list<Shape*>& shapes)
      : shapes_{shapes.begin(), shapes.end()} {}

  CompoundShape(Shape** /* const here makes all shapes in shapes_ point to
                                 the first shape */
                    shapes,
                const size_t size)
      : shapes_{shapes, shapes + size} {}

  CompoundShape(const CompoundShape& other) : shapes_{} {
    for (auto* shape : other.shapes_) {
      shapes_.push_back(shape->clone());
    }
  }

  CompoundShape* clone() const override {
    return new CompoundShape{*this};
  }

  ~CompoundShape() {
    for (auto* shape : shapes_) {
      delete shape;
    }
  }

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

  /** Returns all vertices of the shapes contained by compound shape. */
  std::set<Point> getPoints() const override {
    auto vertices = std::set<Point>{};
    for (const auto* shape : shapes_) {
      vertices.merge(shape->getPoints());
    }
    return vertices;
  }

  Iterator* createIterator(const IteratorFactory* const factory) override {
    return factory->createIterator(shapes_.begin(), shapes_.end());
  }

  void accept(ShapeVisitor* const visitor) override {
    visitor->visitCompoundShape(this);
  }

  void addShape(Shape* const shape) override {
    shapes_.push_back(shape);
  }

  /**
   * Removes the shape from the compound shape and deletes it, does nothing if
   * the target isn't part of the compound shape.
   */
  void deleteShape(Shape* target) override {
    /* from level one */
    const int original_size = shapes_.size();
    shapes_.remove(target);
    if (shapes_.size() != original_size) {
      delete target;
      target = nullptr;
    }

    /* recursively from all levels */
    for (auto* s : shapes_) {
      try {
        s->deleteShape(target);
      } catch (const Shape::ShapeUndeletableException& e) {
        /* silent exception,
         * resemble `rm -f`, which ignores the non-existing error */
      }
    }
  }

  /** Replace the shape under the current compound shape. */
  void replace(Shape* old_shape, Shape* new_shape) {
    for (Shape*& /* & to update */ shape : shapes_) {
      if (shape == old_shape) {
        shape = new_shape;
      }
    }
  }

 private:
  std::list<Shape*> shapes_;
};

#endif /* end of include guard: SRC_COMPOUND_SHAPE_H_ */
