#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"

TEST(DropCommandTest, ExecuteShouldCallDropMethodWithCorrectMousePosition) {
  MockDragAndDrop mock_drag_and_drop;
  CommandHistory history;
  MousePosition::getInstance()->setPos(85.23, 232.7);
  DropCommand dropCommand(&mock_drag_and_drop, &history);

  dropCommand.execute();

  ASSERT_NEAR(85.23, mock_drag_and_drop.getDropX(), 0.001);
  ASSERT_NEAR(232.7, mock_drag_and_drop.getDropY(), 0.001);
}
