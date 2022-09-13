#ifndef SRC_TWO_DIMENSIONAL_VECTOR_H_
#define SRC_TWO_DIMENSIONAL_VECTOR_H_

#include <cmath>
#include <string>

#include "point.h"

class TwoDimensionalVector {
 public:
  TwoDimensionalVector(const Point& head, const Point& tail)
      : head_{head}, tail_{tail} {}

  Point head() const { return head_; }

  Point tail() const { return tail_; }

  std::string info() const {
    return "Vector (" + head_.info() + ", " + tail_.info() + ")";
  }

  double length() const {
    return std::sqrt(x_offset_() * x_offset_() + y_offset_() * y_offset_());
  }

  double dot(const TwoDimensionalVector& that) const {
    return x_offset_() * that.x_offset_() + y_offset_() * that.y_offset_();
  }

  double cross(const TwoDimensionalVector& that) const {
    const double theta = std::acos(dot(that) / (length() * that.length()));
    return (length() * that.length()) * std::sin(theta);
  }

 private:
  Point head_;
  Point tail_;

  double x_offset_() const { return tail_.x() - head_.x(); }

  double y_offset_() const { return tail_.y() - head_.y(); }
};

#endif /* end of include guard: SRC_TWO_DIMENSIONAL_VECTOR_H_ */
