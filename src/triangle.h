#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <cmath>

#include "point.h"
#include "two_dimensional_vector.h"

class Triangle {
 public:
  Triangle(const TwoDimensionalVector& side_1,
           const TwoDimensionalVector& side_2)
      : side_1_{side_1},
        side_2_{side_2},
        side_3_{side_1} /* this is dummy value, will re-assign */ {
    const Point common_point = FindCommonPoint_();
    side_3_ = TwoDimensionalVector{FindUncommonPoint_(side_1, common_point),
                                   FindUncommonPoint_(side_2, common_point)};
  }

  double perimeter() const {
    return side_1_.length() + side_2_.length() + side_3_.length();
  }

  double area() const {
    const double half_perimeter = perimeter() / 2;
    return std::sqrt(half_perimeter * (half_perimeter - side_1_.length()) *
                     (half_perimeter - side_2_.length()) *
                     (half_perimeter - side_3_.length()));
  }

  std::string info() const {
    return "Triangle (" + side_1_.info() + ", " + side_2_.info() + ")";
  }

 private:
  TwoDimensionalVector side_1_;
  TwoDimensionalVector side_2_;
  TwoDimensionalVector side_3_;

  Point FindCommonPoint_() const {
    return side_1_.head() == side_2_.head() || side_1_.head() == side_2_.tail()
               ? side_1_.head()
               : side_1_.tail();
  }

  Point FindUncommonPoint_(const TwoDimensionalVector& side,
                           const Point& common_point) const {
    return side.head() == common_point ? side.tail() : side.head();
  }
};

#endif
