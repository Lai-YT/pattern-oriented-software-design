#ifndef SRC_TWO_DIMENSIONAL_VECTOR_H_
#define SRC_TWO_DIMENSIONAL_VECTOR_H_

#include <cmath>
#include <memory>
#include <string>

#include "point.h"

class TwoDimensionalVector {
 public:
  TwoDimensionalVector(Point* head, Point* tail) : head_{head}, tail_{tail} {
    head = nullptr;
    tail = nullptr;
  }

  Point head() const { return *head_; }

  Point tail() const { return *tail_; }

  std::string info() const {
    return "Vector (" + head_->info() + ", " + tail_->info() + ")";
  }

  double length() const {
    return std::sqrt(x_offset_() * x_offset_() + y_offset_() * y_offset_());
  }

  double dot(const TwoDimensionalVector& that) const {
    return x_offset_() * that.x_offset_() + y_offset_() * that.y_offset_();
  }

  /**
   * Returns the value on z-axis after cross.
   *
   * Since there's no such cross product on 2-dimensional vectors,
   * the z-axis is set as 0, and their cross product will always be
   * (0, 0, some_value).
   */
  double cross(const TwoDimensionalVector& that) const {
    return x_offset_() * that.y_offset_() - y_offset_() * that.x_offset_();
  }

 private:
  std::unique_ptr<Point> head_;
  std::unique_ptr<Point> tail_;

  double x_offset_() const { return tail_->x() - head_->x(); }

  double y_offset_() const { return tail_->y() - head_->y(); }
};

#endif /* end of include guard: SRC_TWO_DIMENSIONAL_VECTOR_H_ */
