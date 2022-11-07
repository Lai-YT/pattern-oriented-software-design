#include "bfs_iterator_factory.h"

#include <list>

#include "../../shape.h"
#include "../bfs_compound_iterator.h"
#include "../iterator.h"

Iterator* BFSIteratorFactory::createIterator(
    const std::list<Shape*>::const_iterator& begin,
    const std::list<Shape*>::const_iterator& end) const {
  return new BFSCompoundIterator<std::list<Shape*>::const_iterator>{begin, end};
};
