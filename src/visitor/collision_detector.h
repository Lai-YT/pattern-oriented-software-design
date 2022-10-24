#ifndef SRC_VISITOR_COLLISION_DETECTOR_H_
#define SRC_VISITOR_COLLISION_DETECTOR_H_

#include <set>
#include <vector>

#include "../bounding_box.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../iterator/iterator.h"
#include "../point.h"
#include "../rectangle.h"
#include "../shape.h"
#include "../triangle.h"
#include "shape_visitor.h"

class CollisionDetector : public ShapeVisitor {
 public:
  CollisionDetector(const Shape* const to_detect_with)
      : bounding_box_{to_detect_with->getPoints()} {}

    void visitCircle(Circle* const circle) override {
    VisitNonCompoundShape_(circle);
  }

  virtual void visitTriangle(Triangle* const triangle) override {
    VisitNonCompoundShape_(triangle);
  }

  virtual void visitRectangle(Rectangle* const rectangle) override {
    VisitNonCompoundShape_(rectangle);
  }

  virtual void visitCompoundShape(CompoundShape* const compound) override {
    std::set<const Point*> vertices = compound->getPoints();
    auto bounding_box_to_detect = BoundingBox{vertices};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      auto factory = ListIteratorFactory{};
      Iterator* it = compound->createIterator(&factory);
      for (it->first(); !it->isDone(); it->next()) {
        it->currentItem()->accept(this);
      }
      delete it;
    }
    for (auto* vertex : vertices) {
      delete vertex;
    }
  }

  std::vector<Shape*> collidedShapes() const {
    return collided_shapes_;
  }

 private:
  BoundingBox bounding_box_;
  std::vector<Shape*> collided_shapes_{};

  void VisitNonCompoundShape_(Shape* non_compound_shape) {
    std::set<const Point*> vertices = non_compound_shape->getPoints();
    auto bounding_box_to_detect = BoundingBox{vertices};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      collided_shapes_.push_back(non_compound_shape);
    }
    for (auto* vertex : vertices) {
      delete vertex;
    }
  }
};

#endif /* end of include guard: SRC_VISITOR_COLLISION_DETECTOR_H_ */
