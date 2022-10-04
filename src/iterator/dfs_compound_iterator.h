#ifndef SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_

#include <list>
#include <stack>

#include "../shape.h"
#include "iterator.h"
#include "null_iterator.h"

template <class ForwarIterator>
class DFSCompoundIterator : public Iterator {
 public:
  /** Range of iteration: [begin, end). */
  DFSCompoundIterator(const ForwarIterator& begin, const ForwarIterator& end)
      : begin_{begin}, end_{end} {}

  /** Restarts the iteration. */
  void first() override {
    to_visit_ = std::stack<Iterator*>{};
    top_level_cursor_ = begin_;
    Visit_(*top_level_cursor_);
    PushChildrenAsToVisitIfNotDone_((*top_level_cursor_)->createDFSIterator());
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

    /* Since every level below guaranteed to be depth-first, the overall
     * traversal is depth-first. */
    if (!cursor_->isDone()) {
      cursor_->next();
    }
    if (cursor_->isDone() && !to_visit_.empty()) {
      cursor_ = to_visit_.top();
      to_visit_.pop();
    }
    if (!cursor_->isDone()) {
      Visit_(cursor_->currentItem());
    }

    /* Since this is DFS,
     * top level shapes are visited each time a sub-tree is finished. */
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
  Iterator* cursor_ = &NullIterator::null_iterator;
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
};

#endif /* end of include guard: SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_ */
