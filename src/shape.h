#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <exception>
#include <set>
#include <string>

#include "iterator/factory/iterator_factory.h"
#include "iterator/iterator.h"
#include "point.h"
#include "visitor/shape_visitor.h"

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
  virtual std::set<const Point*> getPoints() const = 0;
  virtual Iterator* createIterator(const IteratorFactory* const factory) = 0;
  virtual void accept(ShapeVisitor* const visitor) = 0;

  /**
   * Throws ShapeInaddibleException.
   * Compound shapes should override this implementation.
   */
  virtual void addShape(Shape* shape) {
    throw ShapeInaddibleException{""};
  }

  /**
   * Throws ShapeUndeletableException.
   * Compound shapes should override this implementation.
   */
  virtual void deleteShape(Shape* target) {
    throw ShapeUndeletableException{""};
  }

  class ShapeInaddibleException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  class ShapeUndeletableException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
};

#endif /* end of include guard: SRC_SHAPE_H_ */
