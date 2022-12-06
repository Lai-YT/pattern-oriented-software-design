#ifndef SRC_VISITOR_COLLISION_DETECTOR_H_
#define SRC_VISITOR_COLLISION_DETECTOR_H_

#include <memory>
#include <set>
#include <vector>

#include "../bounding_box.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/iterator_factory.h"
#include "../iterator/iterator.h"
#include "../point.h"
#include "../rectangle.h"
#include "../shape.h"
#include "../triangle.h"
#include "shape_visitor.h"

class CollisionDetector : public ShapeVisitor {
 public:
  CollisionDetector(const Shape* const to_detect_with)
      : bounding_box_{to_detect_with->getPointsXX()} {}

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
    const auto bounding_box_to_detect = BoundingBox{compound->getPointsXX()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      IteratorFactory* factory = IteratorFactory::getInstance("List");
      auto itr = std::unique_ptr<Iterator>{compound->createIterator(factory)};
      for (itr->first(); !itr->isDone(); itr->next()) {
        itr->currentItem()->accept(this);
      }
    }
  }

  std::vector<Shape*> collidedShapes() const {
    return collided_shapes_;
  }

 private:
  BoundingBox bounding_box_;
  std::vector<Shape*> collided_shapes_{};

  void VisitNonCompoundShape_(Shape* non_compound_shape) {
    const auto bounding_box_to_detect =
        BoundingBox{non_compound_shape->getPointsXX()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      collided_shapes_.push_back(non_compound_shape);
    }
  }
};

#endif /* end of include guard: SRC_VISITOR_COLLISION_DETECTOR_H_ */
