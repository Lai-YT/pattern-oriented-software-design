#ifndef SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_
#define SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_

#include "../bounding_box.h"
#include "../iterator/factory/bfs_iterator_factory.h"
#include "../iterator/iterator.h"
#include "../shape.h"
#include "shape_visitor.h"

class ClosestShapeFinder : public ShapeVisitor {
 public:
  ClosestShapeFinder(Shape *shape) : target_shape_{shape} {}

  void visitCircle(Circle *circle) override {
    VisitShape_(circle);
  }

  void visitTriangle(Triangle *triangle) override {
    VisitShape_(triangle);
  }

  void visitRectangle(Rectangle *rectangle) override {
    VisitShape_(rectangle);
  }

  /* Compound Shape are not further decomposed. */
  void visitCompoundShape(CompoundShape *compoundShape) override {
    VisitShape_(compoundShape);
  }

  Shape *getClosestShape() const {
    return current_closest_;
  }

  CompoundShape *getParent() const {
    return parent_of_current_closest_;
  }

 private:
  Shape *target_shape_;
  CompoundShape *parent_of_current_closest_ = nullptr;
  Shape *current_closest_ = nullptr;

  void VisitShape_(Shape *shape) {
    /* non compound shape itself is the closest shape */
    if (dynamic_cast<CompoundShape*>(target_shape_) == nullptr) {
      current_closest_ = target_shape_;
      return;
    }

    // auto factory = BFSIteratorFactory{};
    // auto itr = non_compound_shape->createIterator(&factory);
    // auto box_of_target = BoundingBox{target_shape_->getPoints()};
    // double min_distance = 0;
    // for (itr->first(); !itr->isDone();) {
    //   parent_of_current_closest_ = itr->currentItem();
    //   auto box_of_current = BoundingBox{non_compound_shape->getPoints()};
    //   double distance = box_of_current->distance(box_of_target);
    //   if (distance < min_distance) {
    //     min_distance = distance;
    //     current_closest_ = itr->currentItem();
    //   }
    // }
  }
};

#endif /* end of include guard: SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_ */