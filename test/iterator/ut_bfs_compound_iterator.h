#include <gtest/gtest.h>

#include <array>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/bfs_compound_iterator.h"
#include "../../src/iterator/factory/iterator_factory.h"
#include "../../src/iterator/iterator.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"

class BFSCompoundIteratorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  IteratorFactory* bfs_factory_ = IteratorFactory::getInstance("BFS");
};

TEST_F(BFSCompoundIteratorTest,
       CreateIteratorFromEmptyCompoundShapeShouldIsDone) {
  auto compound = CompoundShape{{}};

  auto itr = std::unique_ptr<Iterator>{compound.createIterator(bfs_factory_)};
  itr->first();

  ASSERT_TRUE(itr->isDone());
}

TEST_F(BFSCompoundIteratorTest,
       IteratingWithEmptyCompoundShapeChildShouldBeCorrect) {
  auto compound_child = CompoundShape{{}};
  auto compound = CompoundShape{{&compound_child}};

  auto itr = std::unique_ptr<Iterator>{compound.createIterator(bfs_factory_)};
  itr->first();

  ASSERT_EQ(&compound_child, itr->currentItem());
  itr->next();
  ASSERT_TRUE(itr->isDone());
}

class BFSCompoundIteratorOnFlatListTest : public BFSCompoundIteratorTest {
 protected:
  std::list<Shape*> shapes_{&circle_, &rectangle_, &triangle_};
  BFSCompoundIterator<decltype(shapes_)::iterator> bfs_itr_{shapes_.begin(),
                                                            shapes_.end()};
};

TEST_F(BFSCompoundIteratorOnFlatListTest, TestFirst) {
  bfs_itr_.first();
  ASSERT_EQ(&circle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatListTest,
       FirstShouldBeCalledInitiallyByConstructor) {
  ASSERT_EQ(&circle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatListTest, TestNext) {
  bfs_itr_.first();

  bfs_itr_.next();
  ASSERT_EQ(&rectangle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
  bfs_itr_.next();
  ASSERT_EQ(&triangle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatListTest, FirstShouldRestartIteration) {
  bfs_itr_.first();
  bfs_itr_.next();
  bfs_itr_.next();

  bfs_itr_.first();

  ASSERT_EQ(&circle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatListTest, IsDoneShouldBeFalseWhenNotEnd) {
  bfs_itr_.first();
  ASSERT_FALSE(bfs_itr_.isDone());
  bfs_itr_.next();
  ASSERT_FALSE(bfs_itr_.isDone());
  bfs_itr_.next();
  ASSERT_FALSE(bfs_itr_.isDone());
}

TEST_F(BFSCompoundIteratorOnFlatListTest, TestIsDoneShouldBeTrueWhenEnd) {
  bfs_itr_.first();
  bfs_itr_.next();
  bfs_itr_.next();

  bfs_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(bfs_itr_.isDone());
}

TEST_F(BFSCompoundIteratorOnFlatListTest,
       CurrentItemShouldThrowExceptionWhenEnd) {
  bfs_itr_.first();
  bfs_itr_.next();
  bfs_itr_.next();
  bfs_itr_.next();

  ASSERT_TRUE(bfs_itr_.isDone());
  ASSERT_THROW({ bfs_itr_.currentItem(); }, Iterator::IteratorDoneException)
      << "isDone returns " << bfs_itr_.isDone() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatListTest, NextShouldThrowExceptionWhenEnd) {
  bfs_itr_.first();
  bfs_itr_.next();
  bfs_itr_.next();
  bfs_itr_.next(); /* this one already reaches the end */

  ASSERT_TRUE(bfs_itr_.isDone());
  ASSERT_THROW({ bfs_itr_.next(); }, Iterator::IteratorDoneException)
      << "isDone returns " << bfs_itr_.isDone() << '\n';
}

class BFSCompoundIteratorOnFlatArrayTest : public BFSCompoundIteratorTest {
 protected:
  std::array<Shape*, 3> shapes_{&circle_, &rectangle_, &triangle_};
  BFSCompoundIterator<decltype(shapes_)::iterator> bfs_itr_{shapes_.begin(),
                                                            shapes_.end()};
};

TEST_F(BFSCompoundIteratorOnFlatArrayTest, TestNext) {
  bfs_itr_.first();

  bfs_itr_.next();
  ASSERT_EQ(&rectangle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
  bfs_itr_.next();
  ASSERT_EQ(&triangle_, bfs_itr_.currentItem())
      << bfs_itr_.currentItem()->info() << '\n';
}

TEST_F(BFSCompoundIteratorOnFlatArrayTest, IsDoneShouldBeFalseWhenNotEnd) {
  bfs_itr_.first();
  ASSERT_FALSE(bfs_itr_.isDone());
  bfs_itr_.next();
  ASSERT_FALSE(bfs_itr_.isDone());
  bfs_itr_.next();
  ASSERT_FALSE(bfs_itr_.isDone());
}

TEST_F(BFSCompoundIteratorOnFlatArrayTest, TestIsDoneShouldBeTrueWhenEnd) {
  bfs_itr_.first();
  bfs_itr_.next();
  bfs_itr_.next();

  bfs_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(bfs_itr_.isDone());
}

class BFSCompoundIteratorOnCompoundShapeTest : public BFSCompoundIteratorTest {
 protected:
  /*
   *         com_1
   *      /         \
   *  com_2_1      com_2_2
   *     |      /     |     \
   *    tri com_3_1 com_3_2  tri
   *           |     /   \
   *          rec  cir   rec
   */

  CompoundShape level_three_compound_1_{{&rectangle_}};
  CompoundShape level_three_compound_2_{{&circle_, &rectangle_}};
  CompoundShape level_two_compound_1_{{&triangle_}};
  CompoundShape level_two_compound_2_{
      {&level_three_compound_1_, &level_three_compound_2_, &triangle_}};
  CompoundShape level_one_compound_{
      {&level_two_compound_1_, &level_two_compound_2_}};
  std::unique_ptr<Iterator> bfs_itr_{
      level_one_compound_.createIterator(bfs_factory_)};

  std::string current_info_() const {
    return bfs_itr_->currentItem()->info();
  }
};

TEST_F(BFSCompoundIteratorOnCompoundShapeTest, TestFirst) {
  bfs_itr_->first();

  ASSERT_EQ(&level_two_compound_1_, bfs_itr_->currentItem());
}

TEST_F(BFSCompoundIteratorOnCompoundShapeTest, TestNext) {
  bfs_itr_->first();

  auto bfs_order = std::vector<Shape*>{&level_two_compound_2_,
                                       &triangle_,
                                       &level_three_compound_1_,
                                       &level_three_compound_2_,
                                       &triangle_,
                                       &rectangle_,
                                       &circle_,
                                       &rectangle_};
  for (Shape* s : bfs_order) {
    bfs_itr_->next();

    ASSERT_EQ(s, bfs_itr_->currentItem()) << current_info_() << '\n';
  }
}

TEST_F(BFSCompoundIteratorOnCompoundShapeTest, TestIsDoneShouldBeTrueWhenEnd) {
  bfs_itr_->first();
  for (size_t i = 0; i < 8; i++) {
    bfs_itr_->next();
  }

  bfs_itr_->next();

  ASSERT_TRUE(bfs_itr_->isDone()) << current_info_() << '\n';
}
