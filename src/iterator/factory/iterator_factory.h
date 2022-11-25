#ifndef SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_

#include <list>
#include <string>

class Iterator;
class Shape;

class IteratorFactory {
 public:
  virtual Iterator* createIterator() const;

  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const;

  static IteratorFactory* getInstance(const std::string& type);

  virtual ~IteratorFactory() = default;
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_ */
