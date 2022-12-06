#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_
#define _USE_MATH_DEFINES

#include <cmath>
#include <set>
#include <string>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include "visitor/shape_visitor.h"

class Circle : public Shape {
 public:
  /** The length of the vector is the radius of the circle. */
  Circle(const TwoDimensionalVector* const vector) : Circle{*vector} {}

  Circle(const TwoDimensionalVector& vector) : represent_vector_{vector} {}

  double area() const override {
    return M_PI * radius() * radius();
  }

  double perimeter() const override {
    return 2 * M_PI * radius();
  }

  double radius() const {
    return represent_vector_.length();
  }

  std::string info() const override {
    return "Circle (" + represent_vector_.info() + ")";
  }

  /**
   * Returns the upper right and lower left points which represent the bounding
   * box of the circle.
   *
   * The caller takes the ownership of the points returned.
   * NOTE: So bad that the value type is in pointer since memory spaces they
   * pointed to are not used by circle itself.
   */
  std::set<const Point*> getPoints() const override {
    const auto* upper_right =
        new Point{center_().x() + radius(), center_().y() + radius()};
    const auto* lower_left =
        new Point{center_().x() - radius(), center_().y() - radius()};

    return {upper_right, lower_left};
  }

  Iterator* createIterator(const IteratorFactory* const factory) override {
    return factory->createIterator();
  }

  void accept(ShapeVisitor* const visitor) override {
    visitor->visitCircle(this);
  }

 private:
  TwoDimensionalVector represent_vector_;

  Point center_() const {
    return represent_vector_.head();
  }
};

#endif /* end of include guard: SRC_CIRCLE_H_ */
