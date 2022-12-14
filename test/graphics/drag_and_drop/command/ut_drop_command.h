#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"

class DropCommandTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  MockDragAndDrop mock_drag_and_drop_{};
  CommandHistory history_{};
  DropCommand drop_command_{&mock_drag_and_drop_, &history_};
};

TEST_F(DropCommandTest, ExecuteShouldCallDropWithCurrentMousePosition) {
  const double curr_x = 85.23;
  const double curr_y = 232.7;
  MousePosition::getInstance()->setPos(curr_x, curr_y);

  drop_command_.execute();

  ASSERT_NEAR(curr_x, mock_drag_and_drop_.getDropX(), DELTA);
  ASSERT_NEAR(curr_y, mock_drag_and_drop_.getDropY(), DELTA);
}
