#include <gtest/gtest.h>

#include "iterator/ut_bfs_compound_iterator.h"
#include "iterator/ut_dfs_compound_iterator.h"
#include "iterator/ut_list_compound_iterator.h"
#include "iterator/ut_null_iterator.h"
#include "ut_bounding_box.h"
#include "ut_circle.h"
#include "ut_compound_shape.h"
#include "ut_point.h"
#include "ut_rectangle.h"
#include "ut_triangle.h"
#include "ut_two_dimensional_vector.h"
#include "visitor/ut_collision_detector.h"

int main(int argc, char /* can't be const */ *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
