#ifndef SRC_BOUNDING_BOX_H_
#define SRC_BOUNDING_BOX_H_

#include <algorithm>
#include <exception>
#include <set>

#include "point.h"

class BoundingBox {
 public:
  BoundingBox(const std::set<Point>& points)
      : upper_right_{0, 0}, lower_left_{0, 0} /* place-holding values */ {
    if (points.empty()) {
      throw std::runtime_error{""};
    }
    upper_right_ = Point{CalculateMaxX_(points), CalculateMaxY_(points)};
    lower_left_ = Point{CalculateMinX_(points), CalculateMinY_(points)};
  }

  /** Alias of "max". */
  Point upper_right() const {
    return max();
  }

  Point max() const {
    return upper_right_;
  }

  /** Alias of "min". */
  Point lower_left() const {
    return min();
  }

  Point min() const {
    return lower_left_;
  }

  bool collide(const BoundingBox* const box) const {
    return collide(*box);
  }

  bool collide(const BoundingBox& box) const {
    /* think in reverse: not (not collide) */
    return !(AtRight_(box) || AtLeft_(box) || AtTop_(box) || AtBottom_(box));
  }

  double distance(const BoundingBox* const box) const {
    return lower_left_.distance(box->lower_left()) +
           upper_right_.distance(box->upper_right());
  }

 private:
  Point upper_right_;
  Point lower_left_;

  double CalculateMaxX_(const std::set<Point>& points) const {
    Point point_with_max_x = *std::max_element(
        points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.x() < b.x(); });
    return point_with_max_x.x();
  }

  double CalculateMinX_(const std::set<Point>& points) const {
    Point point_with_min_x = *std::min_element(
        points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.x() < b.x(); });
    return point_with_min_x.x();
  }

  double CalculateMaxY_(const std::set<Point>& points) const {
    Point point_with_max_y = *std::max_element(
        points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.y() < b.y(); });
    return point_with_max_y.y();
  }

  double CalculateMinY_(const std::set<Point>& points) const {
    Point point_with_min_y = *std::min_element(
        points.begin(), points.end(),
        [](const Point& a, const Point& b) { return a.y() < b.y(); });
    return point_with_min_y.y();
  }

  bool AtRight_(const BoundingBox& box) const {
    return box.lower_left().x() > this->upper_right().x();
  }

  bool AtLeft_(const BoundingBox& box) const {
    return box.upper_right().x() < this->lower_left().x();
  }

  bool AtTop_(const BoundingBox& box) const {
    return box.lower_left().y() > this->upper_right().y();
  }

  bool AtBottom_(const BoundingBox& box) const {
    return box.upper_right().y() < this->lower_left().y();
  }
};

#endif /* end of include guard: SRC_BOUNDING_BOX_H_ */
