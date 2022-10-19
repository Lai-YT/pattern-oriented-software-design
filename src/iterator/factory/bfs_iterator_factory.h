#ifndef SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_

#include <list>

#include "../../shape.h"
#include "../bfs_compound_iterator.h"
#include "iterator_factory.h"

class BFSIteratorFactory : public IteratorFactory {
 public:
  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const override {
    return new BFSCompoundIterator<std::list<Shape*>::const_iterator>{begin, end};
  };
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_BFS_ITERATOR_FACTORY_H_ \
        */
