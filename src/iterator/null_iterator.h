#ifndef SRC_ITERATOR_NULL_ITERATOR_H_
#define SRC_ITERATOR_NULL_ITERATOR_H_

#include "iterator.h"

class Shape;

class NullIterator : public Iterator {
 public:
  void first() override {
    throw IteratorDoneException{""};
  }

  void next() override {
    throw IteratorDoneException{""};
  }

  Shape* currentItem() const override {
    throw IteratorDoneException{""};
  }

  bool isDone() const override {
    return true;
  }
};

#endif /* end of include guard: SRC_ITERATOR_NULL_ITERATOR_H_ */
