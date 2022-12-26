#ifndef SRC_GRAPHICS_DRAWING_H_
#define SRC_GRAPHICS_DRAWING_H_

#include <vector>

#include "../shape.h"
#include "observer/subject.h"

class Drawing : public Subject {
 public:
  std::vector<Shape*> shapes() const {
    return shapes_;
  }

  /** @note The ownership of shapes are transferred. */
  Drawing(const std::vector<Shape*>& shapes) : shapes_{shapes} {}

  Drawing(const Drawing& other) = delete; /* prevent shallow copying */

  Drawing& operator=(const Drawing& other) =
      delete; /* prevent shallow copying */

  ~Drawing() {
    for (auto* shape : shapes_) {
      delete shape;
    }
  }

 private:
  std::vector<Shape*> shapes_;
};

#endif /* end of include guard: SRC_GRAPHICS_DRAWING_H_ */