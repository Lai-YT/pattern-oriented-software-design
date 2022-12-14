#include <gtest/gtest.h>

#include <array>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/dfs_compound_iterator.h"
#include "../../src/iterator/factory/iterator_factory.h"
#include "../../src/iterator/iterator.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"

class DFSCompoundIteratorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  IteratorFactory* dfs_factory_ = IteratorFactory::getInstance("DFS");
};

class DFSCompoundIteratorOnFlatListTest : public DFSCompoundIteratorTest {
 protected:
  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  std::list<Shape*> shapes_{&circle_, &rectangle_, &triangle_};
  DFSCompoundIterator<decltype(shapes_)::iterator> dfs_itr_{shapes_.begin(),
                                                            shapes_.end()};
};

TEST_F(DFSCompoundIteratorTest,
       IteratingWithEmptyCompoundShapeChildShouldBeCorrect) {
  Shape* compound_child = new CompoundShape{{}};
  CompoundShape compound{{compound_child}};

  auto itr = std::unique_ptr<Iterator>{compound.createIterator(dfs_factory_)};
  itr->first();

  ASSERT_EQ(compound_child, itr->currentItem());
  itr->next();
  ASSERT_TRUE(itr->isDone());
}

TEST_F(DFSCompoundIteratorOnFlatListTest, TestFirst) {
  dfs_itr_.first();
  ASSERT_EQ(&circle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatListTest,
       FirstShouldBeCalledInitiallyByConstructor) {
  ASSERT_EQ(&circle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatListTest, TestNext) {
  dfs_itr_.first();

  dfs_itr_.next();
  ASSERT_EQ(&rectangle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
  dfs_itr_.next();
  ASSERT_EQ(&triangle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatListTest, FirstShouldRestartIteration) {
  dfs_itr_.first();
  dfs_itr_.next();
  dfs_itr_.next();

  dfs_itr_.first();

  ASSERT_EQ(&circle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatListTest, IsDoneShouldBeFalseWhenNotEnd) {
  dfs_itr_.first();
  ASSERT_FALSE(dfs_itr_.isDone());
  dfs_itr_.next();
  ASSERT_FALSE(dfs_itr_.isDone());
  dfs_itr_.next();
  ASSERT_FALSE(dfs_itr_.isDone());
}

TEST_F(DFSCompoundIteratorOnFlatListTest, TestIsDoneShouldBeTrueWhenEnd) {
  dfs_itr_.first();
  dfs_itr_.next();
  dfs_itr_.next();

  dfs_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(dfs_itr_.isDone());
}

TEST_F(DFSCompoundIteratorOnFlatListTest,
       CurrentItemShouldThrowExceptionWhenEnd) {
  dfs_itr_.first();
  dfs_itr_.next();
  dfs_itr_.next();
  dfs_itr_.next();

  ASSERT_TRUE(dfs_itr_.isDone());
  ASSERT_THROW({ dfs_itr_.currentItem(); }, Iterator::IteratorDoneException)
      << "isDone returns " << dfs_itr_.isDone() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatListTest, NextShouldThrowExceptionWhenEnd) {
  dfs_itr_.first();
  dfs_itr_.next();
  dfs_itr_.next();
  dfs_itr_.next(); /* this one already reaches the end */

  ASSERT_TRUE(dfs_itr_.isDone());
  ASSERT_THROW({ dfs_itr_.next(); }, Iterator::IteratorDoneException)
      << "isDone returns " << dfs_itr_.isDone() << '\n';
}

class DFSCompoundIteratorOnFlatArrayTest : public DFSCompoundIteratorTest {
 protected:
  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  std::array<Shape*, 3> shapes_{&circle_, &rectangle_, &triangle_};
  DFSCompoundIterator<decltype(shapes_)::iterator> dfs_itr_{shapes_.begin(),
                                                            shapes_.end()};
};

TEST_F(DFSCompoundIteratorOnFlatArrayTest, TestNext) {
  dfs_itr_.first();

  dfs_itr_.next();
  ASSERT_EQ(&rectangle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
  dfs_itr_.next();
  ASSERT_EQ(&triangle_, dfs_itr_.currentItem())
      << dfs_itr_.currentItem()->info() << '\n';
}

TEST_F(DFSCompoundIteratorOnFlatArrayTest, IsDoneShouldBeFalseWhenNotEnd) {
  dfs_itr_.first();
  ASSERT_FALSE(dfs_itr_.isDone());
  dfs_itr_.next();
  ASSERT_FALSE(dfs_itr_.isDone());
  dfs_itr_.next();
  ASSERT_FALSE(dfs_itr_.isDone());
}

TEST_F(DFSCompoundIteratorOnFlatArrayTest, TestIsDoneShouldBeTrueWhenEnd) {
  dfs_itr_.first();
  dfs_itr_.next();
  dfs_itr_.next();

  dfs_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(dfs_itr_.isDone());
}

class DFSCompoundIteratorOnCompoundShapeTest : public DFSCompoundIteratorTest {
 protected:
  Circle* circle1_ = new Circle{{{1, 2}, {-3, 5}}};
  Rectangle* rectangle_ = new Rectangle{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle* triangle_ = new Triangle{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  Circle* circle2_ = new Circle{*circle1_};

  /*
   *     compound_1
   *      /      \
   *    cir1   compound_2
   *         /     |      \
   *       rec compound_3 tri
   *               |
   *              cir2
   */

  Shape* level_three_compound_ = new CompoundShape{{circle2_}};
  Shape* level_two_compound_ =
      new CompoundShape{{rectangle_, level_three_compound_, triangle_}};
  CompoundShape level_one_compound_{{circle1_, level_two_compound_}};
  std::unique_ptr<Iterator> dfs_itr_{
      level_one_compound_.createIterator(dfs_factory_)};

  std::string current_info_() const {
    return dfs_itr_->currentItem()->info();
  }
};

TEST_F(DFSCompoundIteratorOnCompoundShapeTest, TestFirst) {
  dfs_itr_->first();

  ASSERT_EQ(circle1_, dfs_itr_->currentItem());
}

TEST_F(DFSCompoundIteratorOnCompoundShapeTest, TestNext) {
  dfs_itr_->first();

  auto dfs_order = std::vector<Shape*>{
      level_two_compound_, rectangle_, level_three_compound_, circle2_,
      triangle_,
  };
  for (Shape* s : dfs_order) {
    dfs_itr_->next();

    ASSERT_EQ(s, dfs_itr_->currentItem()) << current_info_() << '\n';
  }
}

TEST_F(DFSCompoundIteratorOnCompoundShapeTest, TestIsDoneShouldBeTrueWhenEnd) {
  dfs_itr_->first();
  for (size_t i = 0; i < 5; i++) {
    dfs_itr_->next();
  }

  dfs_itr_->next();

  ASSERT_TRUE(dfs_itr_->isDone());
}
