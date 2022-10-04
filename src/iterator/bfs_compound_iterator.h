#ifndef SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_

#include <queue>

#include "../shape.h"
#include "iterator.h"
#include "null_iterator.h"

template <class ForwardIterator>
class BFSCompoundIterator : public Iterator {
 public:
  BFSCompoundIterator(const ForwardIterator& begin, const ForwardIterator& end)
      : begin_{begin}, end_{end} {}

  void first() override {
    to_visit_ = std::queue<Iterator*>{};
    top_level_cursor_ = begin_;
    if (!TopLevelIsDone_()) {
      Visit_(*top_level_cursor_);
      PushChildrenAsToVisitIfNotDone_(
          (*top_level_cursor_)->createBFSIterator());
    }
  }

  void next() override {
    if (isDone()) {
      throw Iterator::IteratorDoneException{
          "can't call next on a done iterator"};
    }
    /* since this is BFS, top level shapes are the first to visit */
    if (!TopLevelIsDone_()) {
      ++top_level_cursor_;
      if (!TopLevelIsDone_()) {
        Visit_(*top_level_cursor_);
        PushChildrenAsToVisitIfNotDone_(
            (*top_level_cursor_)->createBFSIterator());
        return;
      }
    }

    /* Since every level below guaranteed to be breath-first, the overall
     * traversal is breath-first. */
    if (!cursor_->isDone()) {
      cursor_->next();
    }
    if (cursor_->isDone() && !to_visit_.empty()) {
      cursor_ = to_visit_.front();
      to_visit_.pop();
    }
    if (!cursor_->isDone()) {
      Visit_(cursor_->currentItem());
    }
  }

  Shape* currentItem() const override {
    if (isDone()) {
      throw Iterator::IteratorDoneException{
          "can't call currentItem on a done iterator"};
    }
    return current_item_;
  }

  bool isDone() const override {
    return TopLevelIsDone_() && cursor_->isDone() && to_visit_.empty();
  }

 private:
  ForwardIterator begin_;
  ForwardIterator end_;
  ForwardIterator top_level_cursor_;
  Iterator* cursor_ = &NullIterator::null_iterator;
  std::queue<Iterator*> to_visit_{};
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

#endif /* end of include guard: SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_ */
