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
    bool target_shape_is_compound =
        bool(dynamic_cast<CompoundShape *>(target_shape_));
    if (!target_shape_is_compound) {
      current_closest_ = target_shape_;
      return;
    }

    assert(target_shape_is_compound);
    parent_of_current_closest_ = dynamic_cast<CompoundShape *>(target_shape_);

    auto box_of_shape =
        BoundingBox::CreateBoundingBoxWithHeapAllocatedPointsDeleted(
            shape->getPoints());
    auto factory = BFSIteratorFactory{};
    double min_distance = 10000; /* FIXME: bad hack on infinity */
    /* track parent with an addtional pointer */
    CompoundShape *prev_compound = nullptr;
    auto itr = target_shape_->createIterator(&factory);
    for (itr->first(); !itr->isDone(); itr->next()) {
      auto box_of_target =
          BoundingBox::CreateBoundingBoxWithHeapAllocatedPointsDeleted(
              itr->currentItem()->getPoints());
      double distance = box_of_shape.distance(&box_of_target);
      if (distance < min_distance) {
        min_distance = distance;
        current_closest_ = itr->currentItem();
        parent_of_current_closest_ = prev_compound;
      }
      auto *compound = dynamic_cast<CompoundShape *>(itr->currentItem());
      if (compound) {
        prev_compound = compound;
      }
    }
    delete itr;
  }
};

#endif /* end of include guard: SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_ */
