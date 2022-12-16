#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/undo_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class UndoCommandTest : public testing::Test {
 protected:
  MockDragAndDrop drag_and_drop_{};
  CommandHistory command_history_{};
  UndoCommand undo_command_{&drag_and_drop_, &command_history_};
};

TEST_F(UndoCommandTest, ExecuteShouldCallUndoOnCommandHistory) {
  auto* latest_command = new MockCommand{};
  command_history_.addCommand(latest_command);

  undo_command_.execute();

  ASSERT_TRUE(latest_command->isUndoCalled());
}
