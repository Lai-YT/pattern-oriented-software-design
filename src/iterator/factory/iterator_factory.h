#ifndef SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_

#include <list>

// #include "../../shape.h"
#include "../iterator.h"
#include "../null_iterator.h"

class IteratorFactory {
 public:
  virtual Iterator* createIterator() const {
    return new NullIterator{};
  };

  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const {
    return new NullIterator{};
  };
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_ */
