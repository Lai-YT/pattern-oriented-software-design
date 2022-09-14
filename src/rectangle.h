#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <memory>
#include <stdexcept>
#include <string>

#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : public Shape {
 public:
  /* TODO: refactor */
  Rectangle(TwoDimensionalVector* length_side, TwoDimensionalVector* width_side)
      : length_side_{length_side}, width_side_{width_side} {
    length_side = nullptr;
    width_side = nullptr;
    if (length_side_->dot(width_side_.get())) {
      throw NonOrthogonalSideException{""};
    }
    bool head_of_length_side_is_common_point =
        length_side_->head() == width_side_->head() ||
        length_side_->head() == width_side_->tail();
    bool tail_of_length_side_is_common_point =
        length_side_->tail() == width_side_->head() ||
        length_side_->tail() == width_side_->tail();
    if (!head_of_length_side_is_common_point &&
        !tail_of_length_side_is_common_point) {
      throw NoCommonPointException{""};
    }
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

  class NonOrthogonalSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  std::unique_ptr<TwoDimensionalVector> length_side_;
  std::unique_ptr<TwoDimensionalVector> width_side_;
};

#endif /* end of include guard: SRC_RECTANGLE_H_ */
