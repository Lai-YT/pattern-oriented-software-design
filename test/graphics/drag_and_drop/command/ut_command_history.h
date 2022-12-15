#include <gtest/gtest.h>

#include <stack>
#include <vector>

#include "../../../../src/graphics/drag_and_drop/command/command.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "mock_command.h"

TEST(CommandHistoryTest,
     BeginAndEndMacroCommandWithoutAddCommandShouldAddEmptyMacroCommand) {
  CommandHistory history{};

  history.beginMacroCommand();
  history.endMacroCommand();

  const std::stack<Command*> histories = history.getHistory();

  ASSERT_EQ(1, histories.size());
  std::vector<Command*> commands = histories.top()->getCommands();
  ASSERT_TRUE(commands.empty());
}

