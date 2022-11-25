#include "iterator_factory.h"

#include <list>
#include <string>

#include "../../shape.h"
#include "../iterator.h"
#include "../null_iterator.h"

Iterator* IteratorFactory::createIterator() const {
  return new NullIterator{};
}

Iterator* IteratorFactory::createIterator(
    const std::list<Shape*>::const_iterator& begin,
    const std::list<Shape*>::const_iterator& end) const {
  return new NullIterator{};
}

IteratorFactory* IteratorFactory::getInstance(const std::string& type) {
  /* TODO */
  return nullptr;
}
