#ifndef SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_

#include <stdexcept>

#include "iterator.h"

template <class ForwardIterator>
class DFSCompoundIterator : public Iterator {
 public:
  /** Range of iteration: [begin, end). */
  DFSCompoundIterator(const ForwardIterator& begin, const ForwardIterator& end)
      : begin_{begin}, end_{end} {}

  /** Restarts the iteration. */
  void first() override {
    current_ = begin_;
  }

  /** Throws an IteratorDoneException if the iteration reaches the end. */
  const Shape* currentItem() const override {
    if (isDone()) {
      throw IteratorDoneException{""};
    }
    return *current_;
  }

  /** Throws an IteratorDoneException if the iteration reaches the end. */
  void next() override {
    if (isDone()) {
      throw IteratorDoneException{""};
    }
    ++current_;
  }

  bool isDone() const override {
    return *current_ == *end_;
  }

 private:
  const ForwardIterator& begin_;
  const ForwardIterator& end_;
  ForwardIterator current_;
};

#endif /* end of include guard: SRC_ITERATOR_DFS_COMPOUND_ITERATOR_H_ */
