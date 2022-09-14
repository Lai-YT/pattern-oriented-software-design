#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <memory>
#include <string>

#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : Shape {
 public:
  Rectangle(TwoDimensionalVector* length_side, TwoDimensionalVector* width_side)
      : length_side_{length_side}, width_side_{width_side} {
    length_side = nullptr;
    width_side = nullptr;
  }

  double area() const override {
    return length_side_->length() * width_side_->length();
  }

  double perimeter() const override {
    return (length_side_->length() + width_side_->length()) * 2;
  }

  std::string info() const override {
    return "Rectangle (" + length_side_->info() + ", " + width_side_->info() +
           ")";
  }

  double length() const {
    return length_side_->length();
  }

  double width() const {
    return width_side_->length();
  }

 private:
  std::unique_ptr<TwoDimensionalVector> length_side_;
  std::unique_ptr<TwoDimensionalVector> width_side_;
};

#endif /* end of include guard: SRC_RECTANGLE_H_ */
