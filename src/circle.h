#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_
#define _USE_MATH_DEFINES

#include <cmath>
#include <experimental/memory>
#include <string>

#include "shape.h"
#include "two_dimensional_vector.h"

class Circle : public Shape {
 public:
  /** The length of the vector is the radius of the circle. */
  Circle(const TwoDimensionalVector* vector) : represent_vector_{vector} {
    radius_ = represent_vector_->length();
  }

  double area() const override {
    return M_PI * radius_ * radius_;
  }

  double perimeter() const override {
    return 2 * M_PI * radius_;
  }

  double radius() const {
    return radius_;
  }

  std::string info() const override {
    return "Circle (" + represent_vector_->info() + ")";
  }

 private:
  std::experimental::observer_ptr<const TwoDimensionalVector> represent_vector_;
  double radius_;
};

#endif /* end of include guard: SRC_CIRCLE_H_ */
