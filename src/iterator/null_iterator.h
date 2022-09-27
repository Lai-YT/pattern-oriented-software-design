#ifndef SRC_ITERATOR_NULL_ITERATOR_H_
#define SRC_ITERATOR_NULL_ITERATOR_H_

#include <stdexcept>

#include "../shape.h"

class NullIterator {
 public:
  void first() const {
    throw IteratorDoneException{""};
  }

  void next() const {
    throw IteratorDoneException{""};
  }

  Shape* currentItem() const {
    throw IteratorDoneException{""};
  }

  bool isDone() const {
    return true;
  }

  class IteratorDoneException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
};

#endif /* end of include guard: SRC_ITERATOR_NULL_ITERATOR_H_ */
