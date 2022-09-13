#include <sstream>
#include <string>

class Point {
 public:
  Point(const double x, const double y) : x_{x}, y_{y} {}

  double x() const { return x_; }

  double y() const { return y_; }

  /*
   * Returns the point in string "(x, y)".
   *
   * Floating-point numbers are rounded to the second decimal places.
   */
  std::string info() const {
    auto ss = std::stringstream{};
    ss.precision(3);
    ss << '(' << x_ << ", " << y_ << ')';
    return ss.str();
  }

  bool operator==(const Point& that) const {
    return (&that == this) || (that.x_ == this->x_ && that.y_ == this->y_);
  }

  bool operator!=(const Point& that) const { return !operator==(that); }

 private:
  double x_;
  double y_;
};
