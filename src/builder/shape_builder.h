#ifndef SRC_BUILDER_SHAPE_BUILDER_H_
#define SRC_BUILDER_SHAPE_BUILDER_H_

#include <array>
#include <cassert>
#include <set>
#include <stack>
#include <vector>

#include "../circle.h"
#include "../compound_shape.h"
#include "../point.h"
#include "../rectangle.h"
#include "../shape.h"
#include "../triangle.h"
#include "../two_dimensional_vector.h"

/** @brief Returns whether the 2 vectors are orthogonal. */
bool IsOrthogonal(const TwoDimensionalVector& v1,
                  const TwoDimensionalVector& v2);

class ShapeBuilder {
 public:
  /* Does not take the ownership of points. */
  void buildCircle(const Point* center, const Point* on_circle) {
    auto vector = new TwoDimensionalVector{center, on_circle};
    DeleteLater_(vector);
    auto* result = new Circle{vector};
    CompleteBuiltOf_(result);
  }

  void buildCircle(const Point& center, const Point& on_circle) {
    auto* result = new Circle{{center, on_circle}};
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

  void buildTriangle(const Point& v1, const Point& v2, const Point& v3) {
    auto* result = new Triangle{{v1, v2}, {v1, v3}};
    CompleteBuiltOf_(result);
  }

  /**
   * Builds a triangle with v1, v2, v3 as the three vertices,
   * the fourth is deduced.
   *
   * Does not take the ownership of points.
   */
  void buildRectangle(const Point* v1, const Point* v2, const Point* v3) {
    std::array<const TwoDimensionalVector*, 2> sides =
        MakeOrthogonalSides_(v1, v2, v3);
    auto result = new Rectangle{sides.at(0), sides.at(1)};
    CompleteBuiltOf_(result);
  }

  void buildRectangle(const Point& v1, const Point& v2, const Point& v3) {
    std::array<const TwoDimensionalVector*, 2> sides =
        MakeOrthogonalSides_(&v1, &v2, &v3);
    auto result = new Rectangle{*sides.at(0), *sides.at(1)};
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

  std::array<const TwoDimensionalVector*, 2> MakeOrthogonalSides_(
      const Point* v1, const Point* v2, const Point* v3) {
    const Point* common = FindRightAnglePoint_(v1, v2, v3);
    if (!common) {
      throw Rectangle::NonOrthogonalSideException{"sides should be orthogonal"};
    }

    /* Find the 2 uncommon points. */
    auto pool = std::set<const Point*>{v1, v2, v3};
    pool.erase(pool.find(common));

    /* So can we make orthogonal sides. */
    auto sides = std::vector<const TwoDimensionalVector*>{};
    for (const Point* v : pool) {
      sides.push_back(new TwoDimensionalVector{common, v});
    }
    for (auto&& side : sides) {
      DeleteLater_(side);
    }
    assert(sides.size() == 2);
    return {sides.at(0), sides.at(1)};
  }

  const Point* FindRightAnglePoint_(const Point* vertex_1,
                                    const Point* vertex_2,
                                    const Point* vertex_3) const {
    using Vector = TwoDimensionalVector;
    if (IsOrthogonal(Vector{vertex_1, vertex_2}, Vector{vertex_1, vertex_3})) {
      return vertex_1;
    } else if (IsOrthogonal(Vector{vertex_2, vertex_1},
                            Vector{vertex_2, vertex_3})) {
      return vertex_2;
    } else if (IsOrthogonal(Vector{vertex_3, vertex_1},
                            Vector{vertex_3, vertex_2})) {
      return vertex_3;
    }
    return nullptr;
  }
};

bool IsOrthogonal(const TwoDimensionalVector& v1,
                  const TwoDimensionalVector& v2) {
  return v1.dot(v2) == 0;
}

#endif /* end of include guard: SRC_BUILDER_SHAPE_BUILDER_H_ */
