#ifndef SRC_BOUNDING_BOX_H_
#define SRC_BOUNDING_BOX_H_

#include <algorithm>
#include <set>

#include "point.h"

class BoundingBox {
 public:
  BoundingBox(const std::set<Point*>& points)
      : upper_right_{0, 0}, lower_left_{0, 0} /* placeholding values */ {
    if (points.empty()) {
      throw;
    }
    upper_right_ = Point{CalculateMaxX_(points), CalculateMaxY_(points)};
    lower_left_ = Point{CalculateMinX_(points), CalculateMinY_(points)};
  }

  Point upper_right() const {
    return upper_right_;
  }

  Point lower_left() const {
    return lower_left_;
  }

  bool collide(const BoundingBox* const box) const {
    /* think in reverse: not (not collide) */
    return !(AtRight_(box) || AtLeft_(box) || AtTop_(box) || AtBottom_(box));
  }

 private:
  Point upper_right_;
  Point lower_left_;

  double CalculateMaxX_(const std::set<Point*>& points) const {
    double max_x = (*points.begin())->x();
    for (const auto* const point : points) {
      if (point->x() > max_x) {
        max_x = point->x();
      }
    }
    return max_x;
  }

  double CalculateMinX_(const std::set<Point*>& points) const {
    double min_x = (*points.begin())->x();
    for (const auto* const point : points) {
      if (point->x() < min_x) {
        min_x = point->x();
      }
    }
    return min_x;
  }

  double CalculateMaxY_(const std::set<Point*>& points) const {
    double max_y = (*points.begin())->y();
    for (const auto* const point : points) {
      if (point->y() > max_y) {
        max_y = point->y();
      }
    }
    return max_y;
  }

  double CalculateMinY_(const std::set<Point*>& points) const {
    double min_y = (*points.begin())->y();
    for (const auto* const point : points) {
      if (point->y() < min_y) {
        min_y = point->y();
      }
    }
    return min_y;
  }

  bool AtRight_(const BoundingBox* const box) const {
    return box->lower_left().x() >= this->upper_right().x();
  }

  bool AtLeft_(const BoundingBox* const box) const {
    return box->upper_right().x() <= this->lower_left().x();
  }

  bool AtTop_(const BoundingBox* const box) const {
    return box->lower_left().y() >= this->upper_right().y();
  }

  bool AtBottom_(const BoundingBox* const box) const {
    return box->upper_right().y() <= this->lower_left().y();
  }
};

#endif /* end of include guard: SRC_BOUNDING_BOX_H_ */
