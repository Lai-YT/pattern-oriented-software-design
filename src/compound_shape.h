#ifndef SRC_COMPOUND_SHAPE_H_
#define SRC_COMPOUND_SHAPE_H_

#include <algorithm>
#include <list>
#include <string>
#include <vector>

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
    return new DFSCompoundIterator<decltype(shapes_)::iterator>{shapes_.begin(),
                                                                shapes_.end()};
  }

  // Iterator* createBFSIterator() override {}

  void addShape(Shape* const shape) {
    shapes_.push_back(shape);
  }

  /** If target appears multiple times, they are all deleted. */
  void deleteShape(Shape* target) {
    /* Can't delete while iterating because the deleted iterator becomes
     * invalid, and ++ causes segmentation fault. */
    auto targets_found = std::vector<decltype(shapes_)::iterator>{};
    for (auto it = shapes_.begin(); it != shapes_.cend(); ++it) {
      if (*it == target) {
        targets_found.push_back(it);
      }
      if (IsCompoundShape_(*it)) {
        DeleteShapeFromInnerCompoundShape_(dynamic_cast<CompoundShape*>(*it),
                                           target);
      }
    }
    for (const auto& it : targets_found) {
      shapes_.erase(it);
    }
  }

 private:
  std::list<Shape*> shapes_;

  bool IsCompoundShape_(Shape* shape) const {
    return dynamic_cast<CompoundShape*>(shape) != nullptr;
  }

  void DeleteShapeFromInnerCompoundShape_(CompoundShape* compound,
                                          Shape* target) {
    compound->deleteShape(target);
  }
};

#endif /* end of include guard: SRC_COMPOUND_SHAPE_H_ */
