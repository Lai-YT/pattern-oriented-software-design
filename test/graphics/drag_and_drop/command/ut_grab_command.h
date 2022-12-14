#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"

TEST(GrabCommandTest, ExecuteShouldGrabMethodWithCorrectMousePosition) {
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
