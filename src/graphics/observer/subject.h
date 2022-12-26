#ifndef SRC_GRAPHICS_OBSERVER_SUBJECT_H_
#define SRC_GRAPHICS_OBSERVER_SUBJECT_H_

#include <stdexcept>
#include <vector>

#include "observer.h"

class Subject {
 public:
  void attach(Observer* observer) {
    observers_.push_back(observer);
  }

  /** @throw ObserverNotFoundError */
  void detach(Observer* observer) {}

  void notify() {}

  /** @brief Returns the observers for testability. */
  std::vector<Observer*> getObservers() const {
    return observers_;
  }

  virtual ~Subject() = default; /* subject does not own the observers */

  class ObserverNotFoundError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

 private:
  std::vector<Observer*> observers_{};
};

#endif /* end of include guard: SRC_GRAPHICS_OBSERVER_SUBJECT_H_ */