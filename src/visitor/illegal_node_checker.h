#ifndef SRC_VISITOR_ILLEGAL_NODE_CHECKER_H_
#define SRC_VISITOR_ILLEGAL_NODE_CHECKER_H_

#include <memory>

#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/iterator_factory.h"
#include "../iterator/iterator.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "shape_visitor.h"

class IllegalNodeChecker : public ShapeVisitor {
 public:
  /*
   * Non-compound shapes are always legal.
   */

  void visitCircle(Circle* circle) override {
    is_illegal_ = false;
  }

  void visitTriangle(Triangle* triangle) override {
    is_illegal_ = false;
  }

  void visitRectangle(Rectangle* rectangle) override {
    is_illegal_ = false;
  }

  void visitCompoundShape(CompoundShape* compound) override {
    is_illegal_ = IsMissingChildren_(compound);
  }

  /** The result of checking is reset to legal once it's gotten. */
  bool isIllegal() {
    bool result = is_illegal_;
    Reset_();
    return result;
  }

 private:
  bool is_illegal_ = false;

  void Reset_() {
    is_illegal_ = false;
  }

  bool IsMissingChildren_(CompoundShape* compound) {
    if (!HasTwoChildren_(compound)) {
      return true;
    }
    IteratorFactory* factory = IteratorFactory::getInstance("BFS");
    auto itr = std::unique_ptr<Iterator>{compound->createIterator(factory)};
    for (itr->first(); !itr->isDone(); itr->next()) {
      CompoundShape* compound =
          dynamic_cast<CompoundShape*>(itr->currentItem());
      if (compound && IsMissingChildren_(compound)) {
        return true;
      }
    }
    return false;
  }

  bool HasTwoChildren_(CompoundShape* compound) {
    IteratorFactory* factory = IteratorFactory::getInstance("List");
    auto itr = std::unique_ptr<Iterator>{compound->createIterator(factory)};
    int children_count = 0;
    for (itr->first(); !itr->isDone(); itr->next()) {
      ++children_count;
    }
    return children_count == 2;
  }
};

#endif /* end of include guard: SRC_VISITOR_ILLEGAL_NODE_CHECKER_H_ */
