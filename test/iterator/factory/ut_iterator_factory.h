#include <gtest/gtest.h>

#include <array>
#include <chrono>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_set>

#include "../../../src/iterator/factory/bfs_iterator_factory.h"
#include "../../../src/iterator/factory/dfs_iterator_factory.h"
#include "../../../src/iterator/factory/iterator_factory.h"
#include "../../../src/iterator/factory/list_iterator_factory.h"

TEST(IteratorFactoryTest, TestGetInstanceBfsShouldBeIdentical) {
  const std::string type = "BFS";
  IteratorFactory* first_one = IteratorFactory::getInstance(type);

  IteratorFactory* second_one = IteratorFactory::getInstance(type);

  ASSERT_EQ(second_one, first_one);
}

TEST(IteratorFactoryTest, TestGetInstanceDfsShouldBeIdentical) {
  const std::string type = "DFS";
  IteratorFactory* first_one = IteratorFactory::getInstance(type);

  IteratorFactory* second_one = IteratorFactory::getInstance(type);

  ASSERT_EQ(second_one, first_one);
}

TEST(IteratorFactoryTest, TestGetInstanceListShouldBeIdentical) {
  const std::string type = "List";
  IteratorFactory* first_one = IteratorFactory::getInstance(type);

  IteratorFactory* second_one = IteratorFactory::getInstance(type);

  ASSERT_EQ(second_one, first_one);
}

TEST(IteratorFactoryTest, TestConstructorShouldNotBePublic) {
  EXPECT_FALSE(std::is_constructible<IteratorFactory>::value);
  EXPECT_FALSE(std::is_constructible<BFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_constructible<DFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_constructible<ListIteratorFactory>::value);
}

TEST(IteratorFactoryTest, TestCopyConstructorShouldNotBePublic) {
  EXPECT_FALSE(std::is_copy_constructible<IteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_constructible<BFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_constructible<DFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_constructible<ListIteratorFactory>::value);
}

TEST(IteratorFactoryTest, TestCopyAssignmentShouldNotBePublic) {
  EXPECT_FALSE(std::is_copy_assignable<IteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_assignable<BFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_assignable<DFSIteratorFactory>::value);
  EXPECT_FALSE(std::is_copy_assignable<ListIteratorFactory>::value);
}

/* This test is unstable. */
TEST(IteratorFactoryTest,
     TestGetInstanceListShouldBeIdenticalUnderMultiThreading) {
  auto threads = std::array<std::thread, 1000>{};
  auto factories = std::unordered_set<IteratorFactory*>{};
  const std::string type = "BFS";

  for (auto&& thread : threads) {
    thread = std::thread([&type, &factories]() -> void {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      factories.insert(IteratorFactory::getInstance(type));
    });
  }
  for (auto&& thread : threads) {
    thread.join();
  }

  ASSERT_EQ(1, factories.size());
}
