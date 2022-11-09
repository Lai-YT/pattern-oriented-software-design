#ifndef SRC_ITERATOR_LIST_COMPOUND_ITERATOR_H_
#define SRC_ITERATOR_LIST_COMPOUND_ITERATOR_H_

#include "../shape.h"
#include "iterator.h"

template <class ForwardIterator>
class ListCompoundIterator : public Iterator {
 public:
  ListCompoundIterator(const ForwardIterator& begin, const ForwardIterator& end)
      : begin_{begin}, end_{end}, curr_{begin} {}

  void first() override {
    if (isDone()) {
      throw IteratorDoneException{""};
    }
    curr_ = begin_;
  }

  void next() override {
    if (isDone()) {
      throw IteratorDoneException{"can't call next on a done iterator"};
    }
    ++curr_;
  }

  Shape* currentItem() const {
    if (isDone()) {
      throw IteratorDoneException{"can't call currentItem on a done iterator"};
    }
    return *curr_;
  }

  bool isDone() const {
    return curr_ == end_;
  }

 private:
  ForwardIterator begin_;
  ForwardIterator end_;
  ForwardIterator curr_;
};

#endif /* end of include guard: SRC_ITERATOR_LIST_COMPOUND_ITERATOR_H_ */
