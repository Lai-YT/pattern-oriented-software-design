#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <cmath>
#include <memory>
#include <set>
#include <stdexcept>
#include <utility>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include "visitor/shape_visitor.h"

class Triangle : public Shape {
 public:
  Triangle(const TwoDimensionalVector& side_1,
           const TwoDimensionalVector& side_2)
      : side_1_{side_1},
        side_2_{side_2},
        side_3_{{0, 0},
                {0, 0}} /* dummy value since Point has no default ctor */ {
    if (side_1_.cross(side_2_) == 0) {
      throw ParallelSideException{"sides should not be parallel"};
    }
    std::pair<bool, Point> common_point =
        FindCommonPointOfVectors(side_1, side_2_);
    if (!common_point.first) {
      throw NoCommonPointException{"sides should intersect at one end"};
    }
    side_3_ = TwoDimensionalVector{
        FindUncommonPointFromVector(side_1_, common_point.second).second,
        FindUncommonPointFromVector(side_2_, common_point.second).second};
  }

  double perimeter() const override {
    return side_1_.length() + side_2_.length() + side_3_.length();
  }

  double area() const override {
    return std::abs(side_1_.cross(side_2_)) / 2;
  }

  std::string info() const override {
    return "Triangle (" + side_1_.info() + ", " + side_2_.info() + ")";
  }

  /** Returns the three vertices of the triangle. */
  std::set<Point> getPoints() const override {
    const Point common_between_side_1_and_2 =
        FindCommonPointOfVectors(side_1_, side_2_).second;
    const Point uncommon_in_side_2_with_side_1 =
        FindUncommonPointFromVector(side_2_, common_between_side_1_and_2)
            .second;
    return {
        {side_1_.head()}, {side_1_.tail()}, {uncommon_in_side_2_with_side_1}};
  }

  Iterator* createIterator(const IteratorFactory* const factory) {
    return factory->createIterator();
  }

  void accept(ShapeVisitor* const visitor) override {
    visitor->visitTriangle(this);
  }

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class ParallelSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  TwoDimensionalVector side_1_;
  TwoDimensionalVector side_2_;
  TwoDimensionalVector side_3_;
};

#endif /* end of include guard: SRC_TRIANGLE_H_ */
