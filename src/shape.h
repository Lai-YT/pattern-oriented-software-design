#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <string>

#include "iterator/iterator.h"

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
  virtual Iterator* createDFSIterator() = 0;
  virtual void addShape(Shape* shape) {
    /* default for leaf: no effect */
  }
  virtual void deleteShape(Shape* target) {
    /* default for leaf: no effect */
  }
};

#endif /* end of include guard: SRC_SHAPE_H_ */
