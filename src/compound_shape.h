#ifndef SRC_COMPOUND_SHAPE_H_
#define SRC_COMPOUND_SHAPE_H_

#include <list>
#include <string>

#include "iterator/iterator.h"
// #include "iterator/bfs_compound_iterator.h"
#include "iterator/dfs_compound_iterator.h"
#include "shape.h"

class CompoundShape : public Shape {
 public:
  CompoundShape(const std::list<Shape*>& shapes)
      : shapes_{shapes.begin(), shapes.end()} {}

  CompoundShape(Shape** /* const here makes all shapes in shapes_ point to
                                 the first shape */
                    shapes,
                const size_t size)
      : shapes_{shapes, shapes + size} {}

  double area() const override {
    double result = 0;
    for (const auto& shape : shapes_) {
      result += shape->area();
    }
    return result;
  }

  double perimeter() const override {
    double result = 0;
    for (const auto& shape : shapes_) {
      result += shape->perimeter();
    }
    return result;
  }

  std::string info() const override {
    auto inner_info = std::string{};
    for (const auto& shape : shapes_) {
      inner_info += shape->info() + ", ";
    }
    /* remove the last ", " */
    inner_info.pop_back();
    inner_info.pop_back();
    return "CompoundShape (" + inner_info + ")";
  }

  Iterator* createDFSIterator() override {
    return new DFSCompoundIterator{shapes_.begin(), shapes_.end()};
  }

  // Iterator* createBFSIterator() override {}

  // void addShape(Shape* shape) override {}

  // void deleteShape(Shape* shape) override {}
 private:
  std::list<Shape*> shapes_;
};

#endif /* end of include guard: SRC_COMPOUND_SHAPE_H_ */
