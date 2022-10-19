#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_
#define _USE_MATH_DEFINES

#include <cmath>
#include <string>

#include "iterator/factory/iterator_factory.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"

class Circle : public Shape {
 public:
  /** The length of the vector is the radius of the circle. */
  Circle(const TwoDimensionalVector* const vector)
      : represent_vector_{vector} {}

  double area() const override {
    return M_PI * radius() * radius();
  }

  double perimeter() const override {
    return 2 * M_PI * radius();
  }

  double radius() const {
    return represent_vector_->length();
  }

  std::string info() const override {
    return "Circle (" + represent_vector_->info() + ")";
  }

  NullIterator* createDFSIterator() override {
    return new NullIterator{};
  }

  NullIterator* createBFSIterator() override {
    return new NullIterator{};
  }

  NullIterator* createListIterator() override {
    return new NullIterator{};
  }

  Iterator* createIterator(const IteratorFactory* const factory) {
    return factory->createIterator();
  }

 private:
  const TwoDimensionalVector* represent_vector_;
};

#endif /* end of include guard: SRC_CIRCLE_H_ */
