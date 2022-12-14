#ifndef SRC_ITERATOR_ILLEGAL_NODE_ITERATOR_H_
#define SRC_ITERATOR_ILLEGAL_NODE_ITERATOR_H_

#include <list>
#include <memory>

#include "../shape.h"
#include "../visitor/illegal_node_checker.h"
#include "factory/iterator_factory.h"
#include "iterator.h"

/** Iterates the illegal nodes in BFS order. */
class IllegalNodeIterator : public Iterator {
 public:
  IllegalNodeIterator(Shape* root)
      : bfs_itr_{root->createIterator(IteratorFactory::getInstance("BFS"))} {
    first();
  }

  void first() {
    if (!bfs_itr_->isDone()) {
      bfs_itr_->first();
      ToNextIllegal_();
    }
  }

  void next() {
    ToNextIllegal_();
  }

  Shape* currentItem() const {
    return bfs_itr_->currentItem();
  }

  bool isDone() const {
    return bfs_itr_->isDone();
  }

 private:
  std::unique_ptr<Iterator> bfs_itr_;
  IllegalNodeChecker checker_{};

  void ToNextIllegal_() {
    for (; !bfs_itr_->isDone(); bfs_itr_->next()) {
      bfs_itr_->currentItem()->accept(&checker_);
      if (checker_.isIllegal()) {
        break;
      }
    }
  }
};

#endif /* end of include guard: SRC_ITERATOR_ILLEGAL_NODE_ITERATOR_H_ */
