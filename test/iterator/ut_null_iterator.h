#include <gtest/gtest.h>

#include "../../src/iterator/null_iterator.h"

class NullIteratorTest : public ::testing::Test {
 protected:
  NullIterator it{};
};

TEST_F(NullIteratorTest, FirstShouldThrowException) {
  ASSERT_THROW({ it.first(); }, Iterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, CurrentShouldThrowException) {
  ASSERT_THROW({ it.currentItem(); }, Iterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, NextShouldThrowException) {
  ASSERT_THROW({ it.next(); }, Iterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, IsDoneShouldBeTrue) {
  ASSERT_TRUE(it.isDone());
}
