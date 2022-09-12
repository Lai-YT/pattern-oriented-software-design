#include <gtest/gtest.h>

#include "ut_point.h"

int main(int argc, char /* can't be const */ *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
