#ifndef SRC_VISITOR_ILLEGAL_NODE_CHECKER_H_
#define SRC_VISITOR_ILLEGAL_NODE_CHECKER_H_

#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "./shape_visitor.h"

class IllegalNodeChecker : public ShapeVisitor {
 public:
  void visitCircle(Circle *circle) override {}

  void visitTriangle(Triangle *triangle) override {}

  void visitRectangle(Rectangle *rectangle) override {}

  void visitCompoundShape(CompoundShape *compoundShape) override {}

  bool isIllegal() const {}
};

#endif /* end of include guardㄤSRC_VISITOR_ILLEGAL_NODE_CHECKER_H_ */