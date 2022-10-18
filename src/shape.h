#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <exception>
#include <string>

#include "iterator/iterator.h"

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
  virtual Iterator* createDFSIterator() = 0;
  virtual Iterator* createBFSIterator() = 0;
  virtual Iterator* createListIterator() = 0;

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
