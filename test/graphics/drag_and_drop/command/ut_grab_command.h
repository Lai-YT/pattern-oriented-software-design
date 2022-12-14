#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"

class GrabCommandTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  MockDragAndDrop mock_drag_and_drop_{};
  CommandHistory history_{};
  GrabCommand grab_command_{&mock_drag_and_drop_, &history_};
};

TEST_F(GrabCommandTest, ExecuteShouldCallGrabWithCurrentMousePosition) {
  const double curr_x = 85.23;
  const double curr_y = 232.7;
  MousePosition::getInstance()->setPos(curr_x, curr_y);

  grab_command_.execute();

  ASSERT_NEAR(curr_x, mock_drag_and_drop_.getGrabX(), DELTA);
  ASSERT_NEAR(curr_y, mock_drag_and_drop_.getGrabY(), DELTA);
}

TEST_F(GrabCommandTest, UndoWithoutPreCalledExecuteShouldHaveNoEffect) {
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in MockDragAndDrop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);

  grab_command_.undo();

  auto* curr_pos = MousePosition::getInstance();
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getMoveX(), DELTA);
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getMoveY(), DELTA);
}

TEST_F(GrabCommandTest, UndoShouldCallDropWithPreviousMousePosition) {
  const double prev_x = 10;
  const double prev_y = 20;
  MousePosition::getInstance()->setPos(prev_x, prev_y);
  /* to undo, you have to execute first */
  grab_command_.execute();

  grab_command_.undo();

  ASSERT_NEAR(prev_x, mock_drag_and_drop_.getMoveX(), DELTA);
  ASSERT_NEAR(prev_y, mock_drag_and_drop_.getMoveY(), DELTA);
}
