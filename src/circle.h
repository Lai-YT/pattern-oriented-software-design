#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_
#define _USE_MATH_DEFINES

#include <cmath>

#include "two_dimensional_vector.h"

class Circle {
 public:
  /** The length of the vector is the radius of the circle. */
  Circle(const TwoDimensionalVector& vector) : radius_{vector.length()} {}

  double area() const { return M_PI * radius_ * radius_; }

  double perimeter() const { return 2 * M_PI * radius_; }

 private:
  double radius_;
};

#endif /* end of include guard: SRC_CIRCLE_H_ */
