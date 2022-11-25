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
    CompleteBuiltOf_(result);
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
    CompleteBuiltOf_(result);
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
    CompleteBuiltOf_(result);
  }

  void buildCompoundShape() {
    auto* compound_to_build = new CompoundShape{{}, 0};
    compounds_in_built_.push(compound_to_build);
  }

  void buildCompoundEnd() {
    auto compound = compounds_in_built_.top();
    compounds_in_built_.pop();
    CompleteBuiltOf_(compound);
  }

  /* The ownership of the shapes are transferred to the caller, but notice that
   * the inner vectors / shapes are deleted when this builder is out of scope.
   */
  std::vector<Shape*> getResult() {
    std::vector<Shape*> temp = results_;
    results_.clear();
    return temp;
  }

  ~ShapeBuilder() {
    Delete_(results_);
    Delete_(shapes_to_delete_);
    Delete_(vectors_to_delete_);
  }

 private:
  std::vector<Shape*> results_{};
  std::stack<CompoundShape*> compounds_in_built_{};

  /* We lose control over inner vectors / shapes if we don't keep them some
   * where.
   * NOTE: The life time of results_ are bounded by the builder since we'll
   * delete their inner during the destruction. */

  std::vector<const TwoDimensionalVector*> vectors_to_delete_{};
  std::vector<const Shape*> shapes_to_delete_{};

  bool IsBuildingCompound_() const {
    return !compounds_in_built_.empty();
  }

  void DeleteLater_(const TwoDimensionalVector* const to_delete) {
    vectors_to_delete_.push_back(to_delete);
  }

  void DeleteLater_(const Shape* const to_delete) {
    shapes_to_delete_.push_back(to_delete);
  }

  template <typename ForwardIterableContainer>
  void Delete_(ForwardIterableContainer& container) {
    for (auto&& v : container) {
      delete v;
    }
  }

  void CompleteBuiltOf_(Shape* const shape) {
    if (IsBuildingCompound_()) {
      DeleteLater_(shape);
      compounds_in_built_.top()->addShape(shape);
    } else {
      results_.push_back(shape);
    }
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_BUILDER_H_ */
