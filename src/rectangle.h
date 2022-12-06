#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <set>
#include <stdexcept>
#include <string>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include "visitor/shape_visitor.h"

class Rectangle : public Shape {
 public:
  Rectangle(const TwoDimensionalVector* const length_side,
            const TwoDimensionalVector* const width_side)
      : Rectangle{*length_side, *width_side} {}

  Rectangle(const TwoDimensionalVector& length_side,
            const TwoDimensionalVector& width_side)
      : length_side_{length_side}, width_side_{width_side} {
    if (length_side_.dot(width_side_)) {
      throw NonOrthogonalSideException{"sides should be orthogonal"};
    }
    if (FindCommonPointOfVectors(length_side_, width_side_) == nullptr) {
      throw NoCommonPointException{"sides should intersect at one end"};
    }
  }

  double area() const override {
    return length_side_.length() * width_side_.length();
  }

  double perimeter() const override {
    return (length_side_.length() + width_side_.length()) * 2;
  }

  std::string info() const override {
    return "Rectangle (" + length_side_.info() + ", " + width_side_.info() +
           ")";
  }

  double length() const {
    return length_side_.length();
  }

  double width() const {
    return width_side_.length();
  }

  /** Returns the four vertices of the rectangle. */
  std::set<Point> getPointsXX() const override {
    /* Three of the vertices are held by the under-laying vectors
       while the forth has to be derived. */
    const Point common = *FindCommonPointOfVectors(length_side_, width_side_);
    const Point uncommon_in_length =
        *FindUncommonPointFromVector(length_side_, common);
    const Point uncommon_in_width =
        *FindUncommonPointFromVector(width_side_, common);
    return {Point{common}, Point{uncommon_in_length}, Point{uncommon_in_width},
            Point{DeriveTheForthVertex_(common, uncommon_in_length,
                                        uncommon_in_width)}};
  }

  Iterator* createIterator(const IteratorFactory* const factory) {
    return factory->createIterator();
  }

  void accept(ShapeVisitor* const visitor) override {
    visitor->visitRectangle(this);
  }

  class NonOrthogonalSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  TwoDimensionalVector length_side_;
  TwoDimensionalVector width_side_;

  Point DeriveTheForthVertex_(const Point& common, const Point& uncommon_1,
                              const Point& uncommon_2) const {
    double x = uncommon_1.x() + uncommon_2.x() - common.x();
    double y = uncommon_1.y() + uncommon_2.y() - common.y();
    return Point{x, y};
  }
};

#endif /* end of include guard: SRC_RECTANGLE_H_ */
