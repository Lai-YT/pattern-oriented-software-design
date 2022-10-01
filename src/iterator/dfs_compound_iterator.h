#ifndef SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_

#include <list>
#include <stack>

#include "../shape.h"
#include "iterator.h"
#include "null_iterator.h"

class DFSCompoundIterator : public Iterator {
 public:
  /** Range of iteration: [begin, end). */
  DFSCompoundIterator(const std::list<Shape*>::iterator& begin,
                      const std::list<Shape*>::iterator& end)
      : begin_{begin}, end_{end} {}

  /** Restarts the iteration. */
  void first() override {
    to_visit_ = std::stack<Iterator*>{};
    top_level_cursor_ = begin_;
    Visit_(*top_level_cursor_);
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

    if (!cursor_->isDone()) {
      cursor_->next();
    }

    /* look for undone parent */
    while (cursor_->isDone() && !to_visit_.empty()) {
      cursor_ = to_visit_.top();
      to_visit_.pop();
    }

    /* found undone parent */
    if (!cursor_->isDone()) {
      Visit_(cursor_->currentItem());
    }
    /* no undone parent utill top level parent */
    else if (cursor_->isDone() && to_visit_.empty()) {
      ++top_level_cursor_;
      if (!isDone()) {
        Visit_(*top_level_cursor_);
      }
    }
  }

  bool isDone() const override {
    return top_level_cursor_ == end_;
  }

 private:
  std::list<Shape*>::iterator begin_;
  std::list<Shape*>::iterator end_;
  /*
   * Top-level and normal cursors don't share common types. Our iterator returns
   * item by calling currentItem, while standard iterator returns by
   * dereferencing, so we have to handle them separately.
   */
  std::list<Shape*>::iterator top_level_cursor_{};
  Iterator* cursor_ = &NullIterator::null_iterator;
  Shape* current_item_ = nullptr;
  std::stack<Iterator*> to_visit_{};

  void Visit_(Shape* shape) {
    current_item_ = shape;
    PushChildrenAsToVisit_(shape->createDFSIterator());
  }

  void PushChildrenAsToVisit_(Iterator* children) {
    to_visit_.push(children);
    SetFirstIfNotDone_(children);
  }

  void SetFirstIfNotDone_(Iterator* iterator) {
    if (!iterator->isDone()) {
      iterator->first();
    }
  }
};

#endif /* end of include guard: SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_ */
