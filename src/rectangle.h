#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <stdexcept>
#include <string>

#include "iterator/null_iterator.h"
#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : public Shape {
 public:
  Rectangle(const TwoDimensionalVector* const length_side,
            const TwoDimensionalVector* const width_side)
      : length_side_{length_side}, width_side_{width_side} {
    if (length_side_->dot(width_side_)) {
      throw NonOrthogonalSideException{""};
    }
    if (FindCommonPointOfVectors(*length_side_, *width_side_) == nullptr) {
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

  NullIterator* createDFSIterator() override {
    return new NullIterator{};
  }

  NullIterator* createBFSIterator() override {
    return new NullIterator{};
  }

  class NonOrthogonalSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  const TwoDimensionalVector* length_side_;
  const TwoDimensionalVector* width_side_;
};

#endif /* end of include guard: SRC_RECTANGLE_H_ */
