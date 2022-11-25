#include <gtest/gtest.h>

#include "builder/ut_scanner.h"
#include "builder/ut_shape_builder.h"
#include "iterator/factory/ut_iterator_factory.h"
#include "iterator/ut_bfs_compound_iterator.h"
#include "iterator/ut_dfs_compound_iterator.h"
#include "iterator/ut_illegal_node_iterator.h"
#include "iterator/ut_list_compound_iterator.h"
#include "iterator/ut_null_iterator.h"
#include "ut_bounding_box.h"
#include "ut_circle.h"
#include "ut_compound_shape.h"
#include "ut_point.h"
#include "ut_rectangle.h"
#include "ut_triangle.h"
#include "ut_two_dimensional_vector.h"
#include "visitor/ut_closest_shape_finder.h"
#include "visitor/ut_collision_detector.h"
#include "visitor/ut_illegal_node_checker.h"

int main(int argc, char /* can't be const */ *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
