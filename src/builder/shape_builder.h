#ifndef SRC_BUILDER_SHAPE_BUILDER_H_
#define SRC_BUILDER_SHAPE_BUILDER_H_

#include <stack>
#include <vector>

#include "../circle.h"
#include "../compound_shape.h"
#include "../point.h"
#include "../rectangle.h"
#include "../shape.h"
#include "../triangle.h"
#include "../two_dimensional_vector.h"

class ShapeBuilder {
 public:
  /* Does not take the ownership of points. */
  void buildCircle(const Point* center, const Point* on_circle) {
    auto vector = new TwoDimensionalVector{center, on_circle};
    DeleteLater_(vector);
    auto* result = new Circle{vector};

    if (IsBuildingCompound_()) {
      DeleteLater_(result);
      compounds_in_built_.top()->addShape(result);
    } else {
      results_.push_back(result);
    }
  }

  /**
   * Builds a triangle with v1, v2, v3 as the three vertices.
   *
   * Does not take the ownership of points.
   */
  void buildTriangle(const Point* v1, const Point* v2, const Point* v3) {
    auto vec1 = new TwoDimensionalVector{v1, v2};
    auto vec2 = new TwoDimensionalVector{v1, v3};
    DeleteLater_(vec1);
    DeleteLater_(vec2);
    auto* result = new Triangle{vec1, vec2};

    if (IsBuildingCompound_()) {
      DeleteLater_(result);
      compounds_in_built_.top()->addShape(result);
    } else {
      results_.push_back(result);
    }
  }

  /**
   * Builds a triangle with v1, v2, v3 as the three vertices,
   * the fourth is deduced.
   *
   * Does not take the ownership of points.
   */
  void buildRectangle(const Point* v1, const Point* v2, const Point* v3) {
    auto vec1 = new TwoDimensionalVector{v1, v2};
    auto vec2 = new TwoDimensionalVector{v1, v3};
    DeleteLater_(vec1);
    DeleteLater_(vec2);
    auto result = new Rectangle{vec1, vec2};

    if (IsBuildingCompound_()) {
      DeleteLater_(result);
      compounds_in_built_.top()->addShape(result);
    } else {
      results_.push_back(result);
    }
  }

  void buildCompoundShape() {
    auto* compound_to_build = new CompoundShape{{}, 0};
    if (IsBuildingCompound_()) {
      DeleteLater_(compound_to_build);
    }
    compounds_in_built_.push(compound_to_build);
  }

  void buildCompoundEnd() {
    auto compound = compounds_in_built_.top();
    compounds_in_built_.pop();
    if (IsBuildingCompound_()) {
      compounds_in_built_.top()->addShape(compound);
    } else {
      results_.push_back(compound);
    }
  }

  std::vector<Shape*> getResult() {
    std::vector<Shape*> temp = results_;
    results_.clear();
    return temp;
  }

  ~ShapeBuilder() {
    for (auto&& shape : results_) {
      delete shape;
    }
    for (auto&& shape : shapes_to_delete_) {
      delete shape;
    }
    for (auto&& v : vectors_to_delete_) {
      delete v;
    }
  }

 private:
  std::vector<Shape*> results_{};
  std::stack<CompoundShape*> compounds_in_built_{};

  std::vector<TwoDimensionalVector*> vectors_to_delete_{};
  std::vector<Shape*> shapes_to_delete_{};

  bool IsBuildingCompound_() const {
    return !compounds_in_built_.empty();
  }

  void DeleteLater_(TwoDimensionalVector* to_delete) {
    vectors_to_delete_.push_back(to_delete);
  }

  void DeleteLater_(Shape* to_delete) {
    shapes_to_delete_.push_back(to_delete);
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_BUILDER_H_ */
