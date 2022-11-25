#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "../../../src/iterator/factory/bfs_iterator_factory.h"
#include "../../../src/iterator/factory/iterator_factory.h"

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
  ASSERT_FALSE(std::is_constructible<BFSIteratorFactory>::value);
}
