#ifndef SRC_TWO_DIMENSIONAL_VECTOR_H_
#define SRC_TWO_DIMENSIONAL_VECTOR_H_

#include <cmath>
#include <optional>
#include <string>

#include "point.h"

class TwoDimensionalVector {
 public:
  TwoDimensionalVector(const Point* const head, const Point* const tail)
      : TwoDimensionalVector{*head, *tail} {}

  TwoDimensionalVector(const Point& head, const Point& tail)
      : head_{head}, tail_{tail} {}

  /** Alias of "a". */
  Point head() const {
    return a();
  }

  Point a() const {
    return head_;
  }

  /** Alias of "b". */
  Point tail() const {
    return b();
  }

  Point b() const {
    return tail_;
  }

  std::string info() const {
    return "Vector (" + head_.info() + ", " + tail_.info() + ")";
  }

  double length() const {
    return std::sqrt(x_offset_() * x_offset_() + y_offset_() * y_offset_());
  }

  double dot(const TwoDimensionalVector& that) const {
    return x_offset_() * that.x_offset_() + y_offset_() * that.y_offset_();
  }

  double dot(const TwoDimensionalVector* const that) const {
    return dot(*that);
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

  double cross(const TwoDimensionalVector* const that) const {
    return cross(*that);
  }

 private:
  Point head_;
  Point tail_;

  double x_offset_() const {
    return tail_.x() - head_.x();
  }

  double y_offset_() const {
    return tail_.y() - head_.y();
  }
};

bool HasCommonPointWithVector(const Point& point,
                              const TwoDimensionalVector& vector) {
  return point == vector.head() || point == vector.tail();
}

std::optional<Point> FindUncommonPointFromVector(
    const TwoDimensionalVector& vector, const Point& common_point) {
  if (vector.tail() == common_point) {
    return vector.head();
  } else if (vector.head() == common_point) {
    return vector.tail();
  }
  return std::nullopt;
}

std::optional<Point> FindCommonPointOfVectors(
    const TwoDimensionalVector& vector_1,
    const TwoDimensionalVector& vector_2) {
  bool is_head_of_vector_1 =
      HasCommonPointWithVector(vector_1.head(), vector_2);
  bool is_tail_of_vector_1 =
      HasCommonPointWithVector(vector_1.tail(), vector_2);
  if (!is_head_of_vector_1 && !is_tail_of_vector_1) {
    return std::nullopt;
  }
  if (is_head_of_vector_1) {
    return vector_1.head();
  }
  return vector_1.tail();
}

#endif /* end of include guard: SRC_TWO_DIMENSIONAL_VECTOR_H_ */
