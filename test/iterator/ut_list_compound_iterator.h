#include <gtest/gtest.h>

#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/iterator/list_compound_iterator.h"
#include "../../src/point.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "../../src/two_dimensional_vector.h"

class ListCompoundIteratorTest : public ::testing::Test {
 private:
  const Point circle_vector_head_{1, 2};
  const Point circle_vector_tail_{-3, 5};
  const TwoDimensionalVector circle_vector_{&circle_vector_head_,
                                            &circle_vector_tail_};
  const Point rectangle_vector_head_1_{0, 0};
  const Point rectangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector rectangle_vector_1{&rectangle_vector_head_1_,
                                                &rectangle_vector_tail_1_};
  const Point rectangle_vector_head_2_{0, 0};
  const Point rectangle_vector_tail_2_{0, 4};
  const TwoDimensionalVector rectangle_vector_2{&rectangle_vector_head_2_,
                                                &rectangle_vector_tail_2_};
  const Point triangle_vector_head_1_{0, 0};
  const Point triangle_vector_tail_1_{3, 0};
  const TwoDimensionalVector triangle_vector_1_{&triangle_vector_head_1_,
                                                &triangle_vector_tail_1_};
  const Point triangle_vector_head_2_{3, 4};
  const Point triangle_vector_tail_2_{3, 0};
  const TwoDimensionalVector triangle_vector_2_{&triangle_vector_head_2_,
                                                &triangle_vector_tail_2_};

  /* protected after private because non-static data members are initialized in
   * order of declaration in the class definition. */
 protected:
  const double DELTA = 0.001;

  Circle circle_{&circle_vector_};
  Rectangle rectangle_{&rectangle_vector_1, &rectangle_vector_2};
  Triangle triangle_{&triangle_vector_1_, &triangle_vector_2_};
};

class ListCompoundIteratorOnFlatListTest : public ListCompoundIteratorTest {
 protected:
  std::list<Shape*> shapes_{&circle_, &rectangle_, &triangle_};
  ListCompoundIterator<decltype(shapes_)::iterator> list_itr_{shapes_.begin(),
                                                              shapes_.end()};
};

TEST_F(ListCompoundIteratorTest,
       IteratingWithEmptyCompoundShapeChildShouldBeCorrect) {
  auto compound_child = CompoundShape{{}};
  auto compound = CompoundShape{{&compound_child}};

  Iterator* itr = compound.createListIterator();
  itr->first();

  ASSERT_EQ(&compound_child, itr->currentItem());
  itr->next();
  ASSERT_TRUE(itr->isDone());
  delete itr;
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
  ~ListCompoundIteratorOnCompoundShapeTest() override {
    delete list_itr_;
  }

  /*
   *     compound_1
   *      /      \
   *    ci     compound_2
   *         /     |      \
   *       rec compound_3 tri
   *               |
   *              cir
   */

  CompoundShape level_three_compound_{{&circle_}};
  CompoundShape level_two_compound_{
      {&rectangle_, &level_three_compound_, &triangle_}};
  CompoundShape level_one_compound_{{&circle_, &level_two_compound_}};
  Iterator* list_itr_{level_one_compound_.createListIterator()};

  std::string current_info_() const {
    return list_itr_->currentItem()->info();
  }
};

TEST_F(ListCompoundIteratorOnCompoundShapeTest, TestFirst) {
  list_itr_->first();

  ASSERT_EQ(&circle_, list_itr_->currentItem());
}

TEST_F(ListCompoundIteratorOnCompoundShapeTest, TestNext) {
  list_itr_->first();

  auto list_order = std::vector<Shape*>{&circle_, &level_two_compound_};
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
