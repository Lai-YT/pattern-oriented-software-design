#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <string>

#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : Shape {
 public:
  Rectangle(const TwoDimensionalVector& side_1, const TwoDimensionalVector& side_2)
    : side_1_{side_1}, side_2_{side_2} {}

  double area() const override {
    return side_1_.length() * side_2_.length();
  }

  double perimeter() const override {
    return (side_1_.length() + side_2_.length()) * 2;
  }

  std::string info() const override {
    return "Rectangle (" + side_1_.info() + ", " + side_2_.info() + ")";
  }

 private:
  TwoDimensionalVector side_1_;
  TwoDimensionalVector side_2_;
};

#endif /* end of include guard: SRC_RECTANGLE_H_ */
