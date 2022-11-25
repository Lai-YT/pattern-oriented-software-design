#ifndef SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_
#define SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_

#include <list>
#include <memory>
#include <string>
#include <unordered_map>

class Iterator;
class Shape;

/* Singleton pattern: factories ar stateless objects, so we can reuse them. */
class IteratorFactory {
 public:
  virtual Iterator* createIterator() const;

  virtual Iterator* createIterator(
      const std::list<Shape*>::const_iterator& begin,
      const std::list<Shape*>::const_iterator& end) const;

  /* Instances are owned by the factory, do not delete them. */
  static IteratorFactory* getInstance(const std::string& type);

  virtual ~IteratorFactory() = default;

 protected:
  static std::unordered_map<std::string, std::unique_ptr<IteratorFactory>>
      pool_;

 private:
  static bool HasInstanceOf_(const std::string& type);
};

#endif /* end of include guard: SRC_ITERATOR_FACTORY_ITERATOR_FACTORY_H_ */
