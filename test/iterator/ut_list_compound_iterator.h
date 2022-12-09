#include <gtest/gtest.h>

#include <array>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/factory/iterator_factory.h"
#include "../../src/iterator/list_compound_iterator.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"

class ListCompoundIteratorTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  IteratorFactory* list_factory_ = IteratorFactory::getInstance("List");
};

class ListCompoundIteratorOnFlatListTest : public ListCompoundIteratorTest {
 protected:
  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  std::list<Shape*> shapes_{&circle_, &rectangle_, &triangle_};
  ListCompoundIterator<decltype(shapes_)::iterator> list_itr_{shapes_.begin(),
                                                              shapes_.end()};
};

TEST_F(ListCompoundIteratorTest,
       IteratingWithEmptyCompoundShapeChildShouldBeCorrect) {
  Shape* compound_child = new CompoundShape{{}};
  CompoundShape compound{{compound_child}};

  auto itr = std::unique_ptr<Iterator>{compound.createIterator(list_factory_)};
  itr->first();

  ASSERT_EQ(compound_child, itr->currentItem());
  itr->next();
  ASSERT_TRUE(itr->isDone());
}

TEST_F(ListCompoundIteratorOnFlatListTest, TestFirst) {
  list_itr_.first();
  ASSERT_EQ(&circle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatListTest,
       FirstShouldBeCalledInitiallyByConstructor) {
  ASSERT_EQ(&circle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatListTest, TestNext) {
  list_itr_.first();

  list_itr_.next();
  ASSERT_EQ(&rectangle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
  list_itr_.next();
  ASSERT_EQ(&triangle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatListTest, FirstShouldRestartIteration) {
  list_itr_.first();
  list_itr_.next();
  list_itr_.next();

  list_itr_.first();

  ASSERT_EQ(&circle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatListTest, IsDoneShouldBeFalseWhenNotEnd) {
  list_itr_.first();
  ASSERT_FALSE(list_itr_.isDone());
  list_itr_.next();
  ASSERT_FALSE(list_itr_.isDone());
  list_itr_.next();
  ASSERT_FALSE(list_itr_.isDone());
}

TEST_F(ListCompoundIteratorOnFlatListTest, TestIsDoneShouldBeTrueWhenEnd) {
  list_itr_.first();
  list_itr_.next();
  list_itr_.next();

  list_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(list_itr_.isDone());
}

TEST_F(ListCompoundIteratorOnFlatListTest,
       CurrentItemShouldThrowExceptionWhenEnd) {
  list_itr_.first();
  list_itr_.next();
  list_itr_.next();
  list_itr_.next();

  ASSERT_TRUE(list_itr_.isDone());
  ASSERT_THROW({ list_itr_.currentItem(); }, Iterator::IteratorDoneException)
      << "isDone returns " << list_itr_.isDone() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatListTest, NextShouldThrowExceptionWhenEnd) {
  list_itr_.first();
  list_itr_.next();
  list_itr_.next();
  list_itr_.next(); /* this one already reaches the end */

  ASSERT_TRUE(list_itr_.isDone());
  ASSERT_THROW({ list_itr_.next(); }, Iterator::IteratorDoneException)
      << "isDone returns " << list_itr_.isDone() << '\n';
}

class ListCompoundIteratorOnFlatArrayTest : public ListCompoundIteratorTest {
 protected:
  Circle circle_{{{1, 2}, {-3, 5}}};
  Rectangle rectangle_{{{0, 0}, {3, 0}}, {{0, 0}, {0, 4}}};
  Triangle triangle_{{{0, 0}, {3, 0}}, {{3, 4}, {3, 0}}};
  std::array<Shape*, 3> shapes_{&circle_, &rectangle_, &triangle_};
  ListCompoundIterator<decltype(shapes_)::iterator> list_itr_{shapes_.begin(),
                                                              shapes_.end()};
};

TEST_F(ListCompoundIteratorOnFlatArrayTest, TestNext) {
  list_itr_.first();

  list_itr_.next();
  ASSERT_EQ(&rectangle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
  list_itr_.next();
  ASSERT_EQ(&triangle_, list_itr_.currentItem())
      << list_itr_.currentItem()->info() << '\n';
}

TEST_F(ListCompoundIteratorOnFlatArrayTest, IsDoneShouldBeFalseWhenNotEnd) {
  list_itr_.first();
  ASSERT_FALSE(list_itr_.isDone());
  list_itr_.next();
  ASSERT_FALSE(list_itr_.isDone());
  list_itr_.next();
  ASSERT_FALSE(list_itr_.isDone());
}

TEST_F(ListCompoundIteratorOnFlatArrayTest, TestIsDoneShouldBeTrueWhenEnd) {
  list_itr_.first();
  list_itr_.next();
  list_itr_.next();

  list_itr_.next(); /* this one reaches the end */
  ASSERT_TRUE(list_itr_.isDone());
}

class ListCompoundIteratorOnCompoundShapeTest
    : public ListCompoundIteratorTest {
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
  std::unique_ptr<Iterator> list_itr_{
      level_one_compound_.createIterator(list_factory_)};

  std::string current_info_() const {
    return list_itr_->currentItem()->info();
  }
};

TEST_F(ListCompoundIteratorOnCompoundShapeTest, TestFirst) {
  list_itr_->first();

  ASSERT_EQ(circle1_, list_itr_->currentItem());
}

TEST_F(ListCompoundIteratorOnCompoundShapeTest, TestNext) {
  list_itr_->first();

  auto list_order = std::vector<Shape*>{circle1_, level_two_compound_};
  for (Shape* s : list_order) {
    ASSERT_EQ(s, list_itr_->currentItem()) << current_info_() << '\n';

    list_itr_->next();
  }
}

TEST_F(ListCompoundIteratorOnCompoundShapeTest, TestIsDoneShouldBeTrueWhenEnd) {
  list_itr_->first();
  for (size_t i = 0; i < 1; i++) {
    list_itr_->next();
  }

  list_itr_->next();

  ASSERT_TRUE(list_itr_->isDone());
}
