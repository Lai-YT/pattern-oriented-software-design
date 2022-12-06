#include <gtest/gtest.h>

#include "../../src/utils/file_reader.h"

TEST(FileReaderTest, ReadShouldBeCorrect) {
  FileReader reader("test/utils/test_input.txt");
  std::string result = reader.read();
  /* clang-format off */
    ASSERT_EQ(
      "CompoundShape (\n    CompoundShape (\n        Circle (\n            Vector ((0.00, 0.00), (0.00, 5.00))\n        ), Rectangle (\n            Vector ((0.00, 0.00), (0.00, 5.00)),\n            Vector ((0.00, 0.00), (5.00, 0.00))\n        )\n    ), CompoundShape (\n        Circle (\n            Vector ((0.00, 0.00), (0.00, 3.00))\n        )\n    )\n)",
      result
    );
  /* clang-format on */
}
