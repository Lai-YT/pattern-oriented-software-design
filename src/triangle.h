#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <cmath>
#include <memory>

#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Triangle : Shape {
 public:
  Triangle(TwoDimensionalVector* side_1, TwoDimensionalVector* side_2)
      : side_1_{side_1}, side_2_{side_2} {
    side_1 = nullptr;
    side_2 = nullptr;
    const Point common_point = FindCommonPoint_();
    side_3_ = std::unique_ptr<TwoDimensionalVector>{new TwoDimensionalVector{
        new Point{FindUncommonPoint_(*side_1_, common_point)},
        new Point{FindUncommonPoint_(*side_2_, common_point)}}};
  }

  double perimeter() const override {
    return side_1_->length() + side_2_->length() + side_3_->length();
  }

  double area() const override {
    return std::abs(side_1_->cross(side_2_.get())) / 2;
  }

  std::string info() const override {
    return "Triangle (" + side_1_->info() + ", " + side_2_->info() + ")";
  }

 private:
  std::unique_ptr<TwoDimensionalVector> side_1_;
  std::unique_ptr<TwoDimensionalVector> side_2_;
  std::unique_ptr<TwoDimensionalVector> side_3_;

  Point FindCommonPoint_() const {
    bool head_of_side_1_is_common_point = side_1_->head() == side_2_->head() ||
                                          side_1_->head() == side_2_->tail();
    return head_of_side_1_is_common_point ? side_1_->head() : side_1_->tail();
  }

  Point FindUncommonPoint_(const TwoDimensionalVector& side,
                           const Point& common_point) const {
    return side.head() == common_point ? side.tail() : side.head();
  }
};

#endif
