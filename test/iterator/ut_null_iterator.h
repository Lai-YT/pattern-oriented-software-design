#include <gtest/gtest.h>

#include "../../src/iterator/null_iterator.h"

class NullIteratorTest : public ::testing::Test {
 protected:
  NullIterator it{};
};

TEST_F(NullIteratorTest, FirstShouldThrowException) {
  ASSERT_THROW({ it.first(); }, NullIterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, CurrentShouldThrowException) {
  ASSERT_THROW({ it.currentItem(); }, NullIterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, NextShouldThrowException) {
  ASSERT_THROW({ it.next(); }, NullIterator::IteratorDoneException);
}

TEST_F(NullIteratorTest, IsDoneShouldBeTrue) {
  ASSERT_TRUE(it.isDone());
}
