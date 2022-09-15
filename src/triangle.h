#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <cmath>
#include <experimental/memory>
#include <memory>
#include <stdexcept>

#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Triangle : public Shape {
 public:
  Triangle(const TwoDimensionalVector* side_1,
           const TwoDimensionalVector* side_2)
      : side_1_{side_1}, side_2_{side_2} {
    if (side_1_->cross(side_2_.get()) == 0) {
      throw ParallelSideException{""};
    }
    const Point* common_point = FindCommonPoint_();
    if (common_point == nullptr) {
      throw NoCommonPointException{""};
    }
    side_3_ = std::make_unique<TwoDimensionalVector>(
        FindUncommonPoint_(side_1_.get(), common_point),
        FindUncommonPoint_(side_2_.get(), common_point));
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

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class ParallelSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  std::experimental::observer_ptr<const TwoDimensionalVector> side_1_;
  std::experimental::observer_ptr<const TwoDimensionalVector> side_2_;
  std::unique_ptr<const TwoDimensionalVector> side_3_;

  /* TODO: refactor */
  const Point* FindCommonPoint_() const {
    bool head_of_side_1_is_common_point = side_1_->head() == side_2_->head() ||
                                          side_1_->head() == side_2_->tail();
    bool tail_of_side_1_is_common_point = side_1_->tail() == side_2_->head() ||
                                          side_1_->tail() == side_2_->tail();
    if (!head_of_side_1_is_common_point && !tail_of_side_1_is_common_point) {
      return nullptr;
    }
    return head_of_side_1_is_common_point ? side_1_->a() : side_1_->b();
  }

  const Point* FindUncommonPoint_(const TwoDimensionalVector* side,
                                  const Point* common_point) const {
    return *(side->b()) == *common_point ? side->a() : side->b();
  }
};

#endif /* end of include guard: SRC_TRIANGLE_H_ */
