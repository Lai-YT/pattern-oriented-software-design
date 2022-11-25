#ifndef SRC_BUILDER_SHAPE_BUILDER_H_
#define SRC_BUILDER_SHAPE_BUILDER_H_

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
  void buildCircle(const Point* center, const Point* on_circle) {
    auto vector = new TwoDimensionalVector(center, on_circle);
    results_.push_back(new Circle(vector));
    to_deletes_.push_back(vector);
  }

  /**
   * Builds a triangle with v1, v2, v3 as the three vertices.
   *
   * Does not take the ownership of points.
   */
  void buildTriangle(const Point* v1, const Point* v2, const Point* v3) {
    auto vec1 = new TwoDimensionalVector(v1, v2);
    auto vec2 = new TwoDimensionalVector(v1, v3);
    results_.push_back(new Triangle{vec1, vec2});

    to_deletes_.push_back(vec1);
    to_deletes_.push_back(vec2);
  }

  void buildRectangle(const Point* common_point, const Point* v1_point,
                      const Point* v2_point) {}

  void buildCompoundShape() {}

  void buildCompoundEnd() {}

  std::vector<Shape*> getResult() {
    std::vector<Shape*> temp = results_;
    results_.clear();
    return temp;
  }

  ~ShapeBuilder() {
    for (auto&& shape : results_) {
      delete shape;
    }
    for (auto&& v : to_deletes_) {
      delete v;
    }
  }

 private:
  std::vector<Shape*> results_{};
  std::vector<TwoDimensionalVector*> to_deletes_{};
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_BUILDER_H_ */
