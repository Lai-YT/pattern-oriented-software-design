#ifndef SRC_VISITOR_COLLISION_DETECTOR_H_
#define SRC_VISITOR_COLLISION_DETECTOR_H_

#include "../bounding_box.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../iterator/iterator.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "shape_visitor.h"

class CollisionDetector : public ShapeVisitor {
 public:
  CollisionDetector(const std::set<Point*>& points) : bounding_box_{points} {}

  void visitCircle(Circle* circle) override {
    auto bounding_box_to_detect = BoundingBox{circle->getPoints()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      collided_shapes_.push_back(circle);
    }
  }

  virtual void visitTriangle(Triangle* triangle) override {
    auto bounding_box_to_detect = BoundingBox{triangle->getPoints()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      collided_shapes_.push_back(triangle);
    }
  }

  virtual void visitRectangle(Rectangle* rectangle) override {
    auto bounding_box_to_detect = BoundingBox{rectangle->getPoints()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      collided_shapes_.push_back(rectangle);
    }
  }

  virtual void visitCompoundShape(CompoundShape* compound) override {
    auto bounding_box_to_detect = BoundingBox{compound->getPoints()};
    if (bounding_box_.collide(&bounding_box_to_detect)) {
      auto factory = ListIteratorFactory{};
      for (Iterator* it = compound->createIterator(&factory); !it->isDone();
           it->next()) {
        it->currentItem()->accept(this);
      }
    }
  }

  std::vector<Shape*> collidedShapes() const {
    return collided_shapes_;
  }

 private:
  BoundingBox bounding_box_;
  std::vector<Shape*> collided_shapes_{};
};

#endif /* end of include guard: SRC_VISITOR_COLLISION_DETECTOR_H_ */
