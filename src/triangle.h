#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "iterator/null_iterator.h"
#include "point.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Triangle : public Shape {
 public:
  Triangle(const TwoDimensionalVector* const side_1,
           const TwoDimensionalVector* const side_2)
      : side_1_{side_1}, side_2_{side_2} {
    if (side_1_->cross(side_2_) == 0) {
      throw ParallelSideException{""};
    }
    const Point* common_point = FindCommonPointOfVectors(*side_1, *side_2_);
    if (common_point == nullptr) {
      throw NoCommonPointException{""};
    }
    side_3_ = std::unique_ptr<TwoDimensionalVector>{new TwoDimensionalVector{
        FindUncommonPointFromVector(*side_1_, *common_point),
        FindUncommonPointFromVector(*side_2_, *common_point)}};
  }

  double perimeter() const override {
    return side_1_->length() + side_2_->length() + side_3_->length();
  }

  double area() const override {
    return std::abs(side_1_->cross(side_2_)) / 2;
  }

  std::string info() const override {
    return "Triangle (" + side_1_->info() + ", " + side_2_->info() + ")";
  }

  NullIterator* createDFSIterator() override {
    return new NullIterator{};
  }

  class NoCommonPointException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

  class ParallelSideException : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
  };

 private:
  const TwoDimensionalVector* side_1_;
  const TwoDimensionalVector* side_2_;
  std::unique_ptr<const TwoDimensionalVector> side_3_;
};

#endif /* end of include guard: SRC_TRIANGLE_H_ */
