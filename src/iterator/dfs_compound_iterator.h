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
    stack_ = std::stack<Iterator*>{};

    top_level_cursor_ = begin_;
    stack_.push((*top_level_cursor_)->createDFSIterator());
    SetFirstIfNotDone_(stack_.top());
    current_item_ = *top_level_cursor_;
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
    while (cursor_->isDone() && !stack_.empty()) {
      cursor_ = stack_.top();
      stack_.pop();
    }
    if (cursor_->isDone() && stack_.empty()) {
      ++top_level_cursor_;

      if (!isDone()) {
        stack_.push((*top_level_cursor_)->createDFSIterator());
        SetFirstIfNotDone_(stack_.top());

        current_item_ = *top_level_cursor_;
      }
    } else if (!cursor_->isDone()) {
      stack_.push(cursor_->currentItem()->createDFSIterator());
      SetFirstIfNotDone_(stack_.top());
      current_item_ = cursor_->currentItem();
    }
  }

  bool isDone() const override {
    return top_level_cursor_ == end_;
  }

 private:
  NullIterator null_{}; /* a singleton null iterator to point to */

  std::list<Shape*>::iterator begin_;
  std::list<Shape*>::iterator end_;
  std::list<Shape*>::iterator top_level_cursor_;
  Iterator* cursor_ = &null_;
  Shape* current_item_;

  std::stack<Iterator*> stack_{};

  void SetFirstIfNotDone_(Iterator* iterator) {
    if (!iterator->isDone()) {
      iterator->first();
    }
  }
};

#endif /* end of include guard: SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_ */
