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

TEST_F(DropCommandTest, UndoWithoutPreCalledExecuteShouldHaveNoEffect) {
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in MockDragAndDrop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);

  drop_command_.undo();

  auto* curr_pos = MousePosition::getInstance();
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getDropX(), DELTA);
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getDropY(), DELTA);
}

TEST_F(DropCommandTest, UndoShouldCallGrabWithWhereWasDropped) {
  const double dropped_x = 10;
  const double dropped_y = 20;
  MousePosition::getInstance()->setPos(dropped_x, dropped_y);
  /* to undo, you have to execute first */
  drop_command_.execute();

  drop_command_.undo();

  ASSERT_NEAR(dropped_x, mock_drag_and_drop_.getGrabX(), DELTA);
  ASSERT_NEAR(dropped_y, mock_drag_and_drop_.getGrabY(), DELTA);
}
