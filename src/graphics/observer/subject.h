#ifndef SRC_GRAPHICS_OBSERVER_SUBJECT_H_
#define SRC_GRAPHICS_OBSERVER_SUBJECT_H_

#include <stdexcept>
#include <vector>

class Observer;

class Subject {
 public:
  void attach(Observer* observer) {}

  /** @throw ObserverNotFoundError */
  void detach(Observer* observer) {}

  void notify() {}

  /** @brief Returns the observers for testability. */
  std::vector<Observer*> getObservers() const {}

  virtual ~Subject() = default; /* subject does not own the observers */

  class ObserverNotFoundError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
};

#endif /* end of include guard: SRC_GRAPHICS_OBSERVER_SUBJECT_H_ */