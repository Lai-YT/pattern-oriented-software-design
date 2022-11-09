#ifndef SRC_ITERATOR_NULL_ITERATOR_H_
#define SRC_ITERATOR_NULL_ITERATOR_H_

#include "iterator.h"

class Shape;

class NullIterator : public Iterator {
 public:
  void first() override {
    throw IteratorDoneException{"can't call first on a done iterator"};
  }

  void next() override {
    throw IteratorDoneException{"can't call next on a done iterator"};
  }

  Shape* currentItem() const override {
    throw IteratorDoneException{"can't call currentItem on a done iterator"};
  }

  bool isDone() const override {
    return true;
  }
};

#endif /* end of include guard: SRC_ITERATOR_NULL_ITERATOR_H_ */
