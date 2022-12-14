#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"

TEST(GrabCommandTest, ExecuteShouldCallGrabWithCorrectMousePosition) {
  MockDragAndDrop mock_drag_and_drop{};
  CommandHistory history{};
  const double grab_x = 85.23;
  const double grab_y = 232.7;
  MousePosition::getInstance()->setPos(grab_x, grab_y);
  GrabCommand grab_command{&mock_drag_and_drop, &history};

  grab_command.execute();

  ASSERT_NEAR(grab_x, mock_drag_and_drop.getGrabX(), 0.001);
  ASSERT_NEAR(grab_y, mock_drag_and_drop.getGrabY(), 0.001);
}

TEST(GrabCommandTest, UndoWithoutPreCalledExecuteShouldHaveNoEffect) {
  MockDragAndDrop mock_drag_and_drop{};
  CommandHistory history{};
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in mock_drag_and_drop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);
  GrabCommand grab_command{&mock_drag_and_drop, &history};

  grab_command.undo();

  auto* curr_pos = MousePosition::getInstance();
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop.getMoveX(), 0.001);
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop.getMoveY(), 0.001);
}

TEST(GrabCommandTest, UndoShouldCallDropWithPreviousMousePosition) {
  MockDragAndDrop mock_drag_and_drop{};
  CommandHistory history{};
  const double prev_x = 10;
  const double prev_y = 20;
  MousePosition::getInstance()->setPos(prev_x, prev_y);
  GrabCommand grab_command{&mock_drag_and_drop, &history};
  /* to undo, you have to execute first */
  grab_command.execute();

  grab_command.undo();

  ASSERT_NEAR(prev_x, mock_drag_and_drop.getMoveX(), 0.001);
  ASSERT_NEAR(prev_y, mock_drag_and_drop.getMoveY(), 0.001);
}
