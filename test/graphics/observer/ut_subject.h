#include <gtest/gtest.h>

#include <vector>

#include "../../../src/graphics/observer/subject.h"
#include "mock_observer.h"

TEST(SubjectTest, AttachShouldAddObservers) {
  auto subject = Subject{};
  auto observer = MockObserver{};

  subject.attach(&observer);

  std::vector<Observer*> observers = subject.getObservers();
  ASSERT_EQ(1, observers.size());
  ASSERT_EQ(&observer, observers.at(0));
}
