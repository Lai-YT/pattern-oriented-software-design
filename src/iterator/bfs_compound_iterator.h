#ifndef SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_

#include "iterator.h"

template <class ForwardIterator>
class BFSCompoundIterator : Iterator {
 public:
  BFSCompoundIterator(const ForwardIterator& begin, const ForwardIterator& end)
      : begin_{begin}, end_{end} {}

  void first() override {
    cursor_ = begin_;
  }

  void next() override {
    if (isDone()) {
      throw Iterator::IteratorDoneException{""};
    }
    ++cursor_;
  }

  Shape* currentItem() const override {
    if (isDone()) {
      throw Iterator::IteratorDoneException{""};
    }
    return *cursor_;
  }

  bool isDone() const override {
    return cursor_ == end_;
  }

 private:
  ForwardIterator begin_;
  ForwardIterator end_;
  ForwardIterator cursor_;
};

#endif /* end of include guard: SRC_ITERATOR_BFS_COMPOUND_ITERATOR_H_ */
