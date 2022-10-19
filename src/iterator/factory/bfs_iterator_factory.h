#ifndef SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_

#include <list>

#include "iterator_factory.h"

class Iterator;
class Shape;

class BFSIteratorFactory : public IteratorFactory {
 public:
  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const override;
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_ \
        */
