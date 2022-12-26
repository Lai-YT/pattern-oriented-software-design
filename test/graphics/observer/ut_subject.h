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

TEST(SubjectTest, DetachAnAttachedObserverShouldRemoveTheObserver) {
  auto subject = Subject{};
  auto observer_1 = MockObserver{};
  subject.attach(&observer_1);
  auto observer_2 = MockObserver{};
  subject.attach(&observer_2);
  auto observer_3 = MockObserver{};
  subject.attach(&observer_3);

  subject.detach(&observer_2);

  std::vector<Observer*> observers = subject.getObservers();
  ASSERT_EQ(2, observers.size());
  ASSERT_EQ(&observer_1, observers.at(0));
  ASSERT_EQ(&observer_3, observers.at(1));
}

TEST(SubjectTest, DetachUnattachedObserverShouldThrowObserverNotFoundError) {
  auto subject = Subject{};
  auto observer_1 = MockObserver{};
  subject.attach(&observer_1);
  auto observer_2 = MockObserver{};
  subject.attach(&observer_2);
  auto observer_3 = MockObserver{};
  subject.attach(&observer_3);
  auto un_attached_observer = MockObserver{};

  ASSERT_THROW({subject.detach(&un_attached_observer);}, Subject::ObserverNotFoundError);
}

TEST(SubjectTest, NotifyShouldUpdateAllAttachedObservers) {
  auto subject = Subject{};
  auto observer_1 = MockObserver{};
  subject.attach(&observer_1);
  auto observer_2 = MockObserver{};
  subject.attach(&observer_2);

  subject.notify();

  ASSERT_TRUE(observer_1.isUpdated());
  ASSERT_TRUE(observer_2.isUpdated());
}
