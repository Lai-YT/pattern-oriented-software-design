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

  /**
   * Returns all vertices of the shapes contained by compound shape.
   *
   * The caller takes the ownership of the points returned, which are the copies
   * that aren't actually used internally by compound shape itself.
   */
  std::set<const Point*> getPoints() const override {
    /* two points might have same (x, y) but different memory positions,
     * but they should be treated as equal, which means we should not relay on
     * comparing the pointers. */
    auto compare_by_value = [](const Point* p1, const Point* p2) {
      return p1->info() < p2->info();
    };
    auto vertices_with_value_as_compare =
        std::set<const Point*, decltype(compare_by_value)>{compare_by_value};
    for (const auto* shape : shapes_) {
      for (const Point* vertex : shape->getPoints()) {
        if (vertices_with_value_as_compare.count(vertex) != 0) {
          delete vertex;
        } else {
          vertices_with_value_as_compare.insert(vertex);
        }
      }
    }

    /* So bad that the return type is restricted to compare with pointer. */
    return {vertices_with_value_as_compare.begin(),
            vertices_with_value_as_compare.end()};
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

  /** If target appears multiple times, they are all deleted. */
  void deleteShape(Shape* target) override {
    /* from level one */
    shapes_.remove(target);
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
    for (Shape*& shape : shapes_) {
      if (shape == old_shape) {
        shape = new_shape;
      }
    }
  }

 private:
  std::list<Shape*> shapes_;
};

#endif /* end of include guard: SRC_COMPOUND_SHAPE_H_ */
