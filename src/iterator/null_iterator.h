#ifndef SRC_ITERATOR_NULL_ITERATOR_H_
#define SRC_ITERATOR_NULL_ITERATOR_H_

#include "../shape.h"
#include "iterator.h"

class NullIterator : public Iterator {
 public:
  void first() override {
    throw IteratorDoneException{""};
  }

  void next() override {
    throw IteratorDoneException{""};
  }

  const Shape* currentItem() const override {
    throw IteratorDoneException{""};
  }

  bool isDone() const override {
    return true;
  }
};

#endif /* end of include guard: SRC_ITERATOR_NULL_ITERATOR_H_ */
