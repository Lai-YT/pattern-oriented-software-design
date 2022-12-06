#ifndef SRC_GRAPHIC_CANVAS_H_
#define SRC_GRAPHIC_CANVAS_H_

class Circle;
class Triangle;
class Rectangle;

class Canvas {
 public:
  virtual ~Canvas() = default;
  virtual void drawCircle(const Circle* cir) const = 0;
  virtual void drawTriangle(const Triangle* tri) const = 0;
  virtual void drawRectangle(const Rectangle* rect) const = 0;
  virtual void display() = 0;
};

#endif /* end of include guard: SRC_GRAPHIC_CANVAS_H_ */
