#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/undo_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class UndoCommandTest : public testing::Test {
 protected:
  MockDragAndDrop drag_and_drop_{};
  CommandHistory command_history_{};
};

TEST_F(UndoCommandTest, ExecuteShouldCallUndoOnCommandHistory) {
  auto* latest_command = new MockCommand{};
  command_history_.addCommand(latest_command);
  UndoCommand undo_command{&drag_and_drop_, &command_history_};

  undo_command.execute();

  ASSERT_TRUE(latest_command->isUndoCalled());
}
