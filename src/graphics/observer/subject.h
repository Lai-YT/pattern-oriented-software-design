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
  void detach(Observer* observer) {
    auto itr = observers_.cbegin();
    bool not_found = true;
    while (itr != observers_.cend()) {
      if ((*itr) == observer) {
        /* a single observer may be attached multiple times */
        itr = observers_.erase(itr);
        not_found = false;
      } else {
        itr++;
      }
    }
    if (not_found) {
      throw ObserverNotFoundError{
          "the observer wasn't attached to the subject."};
    }
  }

  void notify() {
    for (auto* observer : observers_) {
      observer->update();
    }
  }

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