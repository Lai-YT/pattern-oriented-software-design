#ifndef SRC_SHAPE_H_
#define SRC_SHAPE_H_

#include <string>

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual std::string info() const = 0;
};

#endif