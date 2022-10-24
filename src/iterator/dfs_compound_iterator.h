#ifndef SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_

#include <stack>

#include "../shape.h"
#include "iterator.h"
#include "null_iterator.h"

template <class ForwarIterator>
class DFSCompoundIterator : public Iterator {
 public:
  /** Range of iteration: [begin, end). */
  DFSCompoundIterator(const ForwarIterator& begin, const ForwarIterator& end)
      : begin_{begin}, end_{end} {
    first();
  }

  ~DFSCompoundIterator() {
    delete cursor_;
  }

  /** Restarts the iteration. */
  void first() override {
    ClearToVisit_();
    top_level_cursor_ = begin_;
    /* the range might be empty */
    if (!TopLevelIsDone_()) {
      Visit_(*top_level_cursor_);
      PushChildrenAsToVisitIfNotDone_(
          (*top_level_cursor_)->createDFSIterator());
    }
  }

  /** Throws an IteratorDoneException if the iteration reaches the end. */
  Shape* currentItem() const override {
    if (isDone()) {
      throw IteratorDoneException{""};
    }
    return current_item_;
  }

  /** Throws an IteratorDoneException if the iteration reaches the end. */
  void next() override {
    if (isDone()) {
      throw IteratorDoneException{""};
    }

    /*
     * The composite property:
     *  Use recursion, which means to only care about the top level.
     *  Since every level below are guaranteed to be depth-first, the overall
     *  traversal is depth-first.
     */
    if (!cursor_->isDone()) {
      cursor_->next();
    }
    if (cursor_->isDone() && !to_visit_.empty()) {
      delete cursor_;
      cursor_ = to_visit_.top();
      to_visit_.pop();
    }
    if (!cursor_->isDone()) {
      Visit_(cursor_->currentItem());
    }
    /* Top level shapes are visited each time a sub-tree is finished. */
    if (cursor_->isDone() && to_visit_.empty()) {
      ++top_level_cursor_;
      if (!isDone()) {
        Visit_(*top_level_cursor_);
        PushChildrenAsToVisitIfNotDone_(
            (*top_level_cursor_)->createDFSIterator());
      }
    }
  }

  bool isDone() const override {
    return TopLevelIsDone_() && cursor_->isDone() && to_visit_.empty();
  }

 private:
  ForwarIterator begin_;
  ForwarIterator end_;
  /*
   * Top-level and normal cursors don't share common types. Our iterator returns
   * item by calling currentItem, while pointers and standard iterator returns
   * by dereferencing, so we have to handle them separately.
   */
  ForwarIterator top_level_cursor_{};
  Iterator* cursor_ = new NullIterator{};
  std::stack<Iterator*> to_visit_{};
  Shape* current_item_ = nullptr;

  bool TopLevelIsDone_() const {
    return top_level_cursor_ == end_;
  }

  void Visit_(Shape* shape) {
    current_item_ = shape;
  }

  void PushChildrenAsToVisitIfNotDone_(Iterator* children) {
    if (!children->isDone()) {
      children->first();
      to_visit_.push(children);
    }
  }

  void ClearToVisit_() {
    while (!to_visit_.empty()) {
      delete to_visit_.top();
      to_visit_.pop();
    }
  }
};

#endif /* end of include guard: SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_ */
