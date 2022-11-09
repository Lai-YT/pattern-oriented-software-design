#ifndef SRC_ITERATOR_FACTORY_ILLEGAL_NODE_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_ILLEGAL_NODE_ITERATOR_FACTORY_H_

#include <list>

#include "../illegal_node_iterator.h"
#include "../iterator.h"
#include "iterator_factory.h"

class Shape;

class IllegalNodeIteratorFactory : public IteratorFactory {
 public:
  virtual Iterator* createIterator() const {
    return new IllegalNodeIterator{root_};
  }

  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const {
    return new IllegalNodeIterator{root_};
  }

  IllegalNodeIteratorFactory(Shape* root) : root_(root) {}

 private:
  Shape* root_;
};

#endif /* end of include guard: \
          SRC_ITERATOR_FACTORY_ILLEGAL_NODE_ITERATOR_FACTORY_H_ */
