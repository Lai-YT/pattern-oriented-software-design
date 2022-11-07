#ifndef SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_
#define SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_

#include "./shape_visitor.h"
#include "../shape.h"

class ClosestShapeFinder : public ShapeVisitor {
 public:
  ClosestShapeFinder(Shape *shape) {}

  void visitCircle(Circle *circle) override {}

  void visitTriangle(Triangle *triangle) override {}

  void visitRectangle(Rectangle *rectangle) override {}

  void visitCompoundShape(CompoundShape *compoundShape) override {}

  Shape *getClosestShape() const {}

  CompoundShape *getParent() const {}

 private:
  Shape* parent_of_current_closest_ = nullptr;
  Shape* current_closest_;
};

#endif /* end of include guard: SRC_VISITOR_CLOSEST_SHAPE_FINDER_H_ */