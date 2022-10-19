#include "list_iterator_factory.h"

#include <list>

#include "../../shape.h"
#include "../iterator.h"
#include "../list_compound_iterator.h"

Iterator* ListIteratorFactory::createIterator(
    const std::list<Shape*>::const_iterator& begin,
    const std::list<Shape*>::const_iterator& end) const {
  return new ListCompoundIterator<std::list<Shape*>::const_iterator>{begin,
                                                                     end};
};
