#ifndef SRC_ITERATOR_H_
#define SRC_ITERATOR_H_

#include <stdexcept>

class Iterator {
 public:
  virtual ~Iterator() = default;
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Shape* currentItem() const = 0;
  virtual bool isDone() const = 0;

  class IteratorDoneException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
};

#endif /* end of include guard: SRC_ITERATOR_H_ */
