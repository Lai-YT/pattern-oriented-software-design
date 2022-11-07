#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include <ios>
#include <sstream>
#include <string>

class Point {
 public:
  Point(const double x, const double y) : x_{x}, y_{y} {}

  double x() const {
    return x_;
  }

  double y() const {
    return y_;
  }

  /**
   * Returns the point in string "(x, y)".
   *
   * Numbers are rounded or padded to the second decimal places.
   */
  std::string info() const {
    auto ss = std::stringstream{};
    ss.precision(2);
    ss << std::fixed;
    ss << '(' << x_ << ", " << y_ << ')';
    return ss.str();
  }

  /**
   * Points with their x, y values the same correspondingly after rounded to the
   * second decimal places are considered as equal.
   */
  bool operator==(const Point& that) const {
    return (&that == this) || HasEqualXY_(that);
  }

  bool operator!=(const Point& that) const {
    return !operator==(that);
  }

 private:
  double x_;
  double y_;

  bool HasEqualXY_(const Point& that) const {
    return that.info() == info();
  }
};

#endif /* end of include guard: SRC_POINT_H_ */
