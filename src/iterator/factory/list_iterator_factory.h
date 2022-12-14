#ifndef SRC_ITERATOR_FACTORY_LIST_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_LIST_ITERATOR_FACTORY_H_

#include <list>
#include <string>

#include "iterator_factory.h"

class Iterator;
class Shape;

class ListIteratorFactory : public IteratorFactory {
 public:
  Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const override;

 private:
  friend IteratorFactory* IteratorFactory::getInstance(const std::string& type);

  ListIteratorFactory() = default;
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_LIST_ITERATOR_FACTORY_H_ \
        */
