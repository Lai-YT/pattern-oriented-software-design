#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class TriangleTest : public ::testing::Test {
 protected:
  const double DELTA = 0.001;

  TriangleTest()
      : vector_1_{TwoDimensionalVector(&vector_head_1_, &vector_tail_1_)},
        vector_2_{TwoDimensionalVector(&vector_head_2_, &vector_tail_2_)} {
    triangle_ = new Triangle{&vector_1_, &vector_2_};
  }

  virtual ~TriangleTest() override {
    delete triangle_;
  }

  Triangle* triangle_;

 private:
  const Point vector_head_1_ = Point{0, 0};
  const Point vector_tail_1_ = Point{3, 0};
  const TwoDimensionalVector vector_1_;
  const Point vector_head_2_ = Point{3, 4};
  const Point vector_tail_2_ = Point{3, 0};
  const TwoDimensionalVector vector_2_;
};

TEST_F(TriangleTest, TestPerimeter) {
  ASSERT_NEAR(12, triangle_->perimeter(), DELTA);
}

TEST_F(TriangleTest, TestArea) {
  ASSERT_NEAR(6, triangle_->area(), DELTA);
}

TEST_F(TriangleTest, TestInfo) {
  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      triangle_->info());
}

TEST_F(TriangleTest, PassingVectorsWithNoCommonPointShoudThrowException) {
  const auto vector_head_1 = Point{0, 0};
  const auto vector_tail_1 = Point{4, 0};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{3, 4};
  const auto vector_tail_2 = Point{3, 0};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto triangle = Triangle(&vector_1, &vector_2); },
               Triangle::NoCommonPointException);
}

TEST_F(TriangleTest, PassingParallelVectorsShoudThrowException) {
  const auto vector_head_1 = Point{0, 0};
  const auto vector_tail_1 = Point{4, 0};
  const auto vector_1 = TwoDimensionalVector{&vector_head_1, &vector_tail_1};
  const auto vector_head_2 = Point{4, 0};
  const auto vector_tail_2 = Point{5, 0};
  const auto vector_2 = TwoDimensionalVector{&vector_head_2, &vector_tail_2};

  ASSERT_THROW({ const auto triangle = Triangle(&vector_1, &vector_2); },
               Triangle::ParallelSideException);
}

TEST_F(TriangleTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = triangle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}

class TrianglePolymorphismTest : public TriangleTest {
 protected:
  TrianglePolymorphismTest() : TriangleTest{} {
    triangle_ = TriangleTest::triangle_;
  }

  Shape* triangle_;
};

TEST_F(TrianglePolymorphismTest, TestPerimeter) {
  ASSERT_NEAR(12, triangle_->perimeter(), DELTA);
}

TEST_F(TrianglePolymorphismTest, TestArea) {
  ASSERT_NEAR(6, triangle_->area(), DELTA);
}

TEST_F(TrianglePolymorphismTest, TestInfo) {
  ASSERT_EQ(
      "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), "
      "(3.00, 0.00)))",
      triangle_->info());
}

TEST_F(TrianglePolymorphismTest, TestCreateDfsIterator) {
  Iterator* dfs_iter = triangle_->createDFSIterator();

  ASSERT_TRUE(dfs_iter->isDone());

  delete dfs_iter;
}
