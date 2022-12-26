#ifndef SRC_GRAPHICS_DRAWING_H_
#define SRC_GRAPHICS_DRAWING_H_

#include <vector>

#include "../shape.h"
#include "observer/subject.h"

class Drawing : public Subject {
 public:
  std::vector<Shape*> shapes() const {}

  Drawing(const std::vector<Shape*>& shapes) {}

  ~Drawing() {}
};

#endif /* end of include guard: SRC_GRAPHICS_DRAWING_H_ */