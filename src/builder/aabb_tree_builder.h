#ifndef SRC_BUILDER_AABB_TREE_BUILDER_H_
#define SRC_BUILDER_AABB_TREE_BUILDER_H_

#include "../point.h"
#include "../shape.h"

class AABBTreeBuilder {
 public:
  void insertTriangle(const Point *common_point, const Point *v1_point,
                      const Point *v2_point) {}

  void insertCircle(const Point *center, const Point *to_radius) {}

  void insertRectangle(const Point *common_point, const Point *v1_point,
                       const Point *v2_point) {}

  Shape *getTree() const {}
};

#endif /* end of include guard: SRC_BUILDER_AABB_TREE_BUILDER_H_ */
