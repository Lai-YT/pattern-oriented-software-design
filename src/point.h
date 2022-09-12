#include <sstream>
#include <string>

class Point {
 public:
  Point(const double x, const double y) : x_{x}, y_{y} {}

  double x() const { return x_; }

  double y() const { return y_; }

  std::string info() const {
    auto ss = std::stringstream{};
    ss.precision(3);
    ss << '(' << x_ << ", " << y_ << ')';
    return ss.str();
  }

 private:
  double x_;
  double y_;
};
