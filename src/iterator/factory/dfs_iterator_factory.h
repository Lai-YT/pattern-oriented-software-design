#ifndef SRC_ITERATOR_FACTORY_DFS_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_DFS_ITERATOR_FACTORY_H_

#include <list>

#include "../../shape.h"
#include "../dfs_compound_iterator.h"
#include "iterator_factory.h"

class DFSIteratorFactory : public IteratorFactory {
 public:
  virtual Iterator* createIterator(const std::list<Shape*>::iterator& begin,
                                   const std::list<Shape*>::iterator& end) {
    return new DFSCompoundIterator<std::list<Shape*>::iterator>{begin, end};
  };
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_DFS_ITERATOR_FACTORY_H_ \
        */
