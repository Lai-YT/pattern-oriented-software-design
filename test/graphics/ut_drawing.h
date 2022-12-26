#include <gtest/gtest.h>

#include <vector>

#include "../../src/graphics/drawing.h"
#include "observer/mock_observer.h"

TEST(DrawingTest, AttachShouldAddObservers) {
  auto drawing = Drawing{{}};
  auto observer = MockObserver{};

  drawing.attach(&observer);

  std::vector<Observer*> observers = drawing.getObservers();
  ASSERT_EQ(1, observers.size());
  ASSERT_EQ(&observer, observers.at(0));
}

TEST(DrawingTest, DetachAnAttachedObserverShouldRemoveTheObserver) {
  auto drawing = Drawing{{}};
  auto observer_1 = MockObserver{};
  drawing.attach(&observer_1);
  auto observer_2 = MockObserver{};
  drawing.attach(&observer_2);
  auto observer_3 = MockObserver{};
  drawing.attach(&observer_3);

  drawing.detach(&observer_2);

  std::vector<Observer*> observers = drawing.getObservers();
  ASSERT_EQ(2, observers.size());
  ASSERT_EQ(&observer_1, observers.at(0));
  ASSERT_EQ(&observer_3, observers.at(1));
}

TEST(DrawingTest, DetachUnattachedObserverShouldThrowObserverNotFoundError) {
  auto drawing = Drawing{{}};
  auto observer_1 = MockObserver{};
  drawing.attach(&observer_1);
  auto observer_2 = MockObserver{};
  drawing.attach(&observer_2);
  auto observer_3 = MockObserver{};
  drawing.attach(&observer_3);
  auto un_attached_observer = MockObserver{};

  ASSERT_THROW({ drawing.detach(&un_attached_observer); },
               Drawing::ObserverNotFoundError);
}

TEST(DrawingTest, NotifyShouldUpdateAllAttachedObservers) {
  auto drawing = Drawing{{}};
  auto observer_1 = MockObserver{};
  drawing.attach(&observer_1);
  auto observer_2 = MockObserver{};
  drawing.attach(&observer_2);

  drawing.notify();

  ASSERT_TRUE(observer_1.isUpdated());
  ASSERT_TRUE(observer_2.isUpdated());
}
