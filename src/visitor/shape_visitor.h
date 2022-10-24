#ifndef SRC_VISITOR_SHAPE_VISITOR_H_
#define SRC_VISITOR_SHAPE_VISITOR_H_

class Circle;
class Triangle;
class Rectangle;
class CompoundShape;

class ShapeVisitor {
 public:
  virtual void visitCircle(Circle* circle) = 0;
  virtual void visitTriangle(Triangle* triangle) = 0;
  virtual void visitRectangle(Rectangle* rectangle) = 0;
  virtual void visitCompoundShape(CompoundShape* compound) = 0;
  virtual ~ShapeVisitor() = default;
};

#endif /* end of include guard: SRC_VISITOR_SHAPE_VISITOR_H_ */
