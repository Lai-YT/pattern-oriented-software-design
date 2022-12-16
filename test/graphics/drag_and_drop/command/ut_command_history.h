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

TEST(CommandHistoryTest,
     BeginMacroCommandShouldAddAnEmptyMacroIntoHistoryAlthoughNotEndedYet) {
  CommandHistory history{};

  history.beginMacroCommand();

  const std::stack<Command*> histories = history.getHistory();

  ASSERT_EQ(1, histories.size());
  std::vector<Command*> commands = histories.top()->getCommands();
  ASSERT_TRUE(commands.empty());
}

TEST(CommandHistoryTest,
     BeginAndEndMacroCommandWithAddCommandShouldBuildInCorrectCompositeManner) {
  auto* child_command_1_ = new MockCommand{};
  auto* child_command_2_ = new MockCommand{};
  auto* child_command_3_ = new MockCommand{};
  auto* child_command_4_ = new MockCommand{};
  CommandHistory history{};

  /*
   * History (reversed with respect to the order they are added):
   *  Command 4
   *  Macro {
   *    Command 1
   *    Macro {
   *      Command 2
   *      Command 3
   *    }
   *  }
   */
  history.beginMacroCommand();
  history.addCommand(child_command_1_);
  history.beginMacroCommand();
  history.addCommand(child_command_2_);
  history.addCommand(child_command_3_);
  history.endMacroCommand();
  history.endMacroCommand();
  history.addCommand(child_command_4_);

  /* make the feeling of levels with block */
  std::stack<Command*> histories = history.getHistory();
  ASSERT_EQ(2, histories.size());
  ASSERT_EQ(child_command_4_, histories.top());
  histories.pop();
  {
    auto* level_one_macro = dynamic_cast<MacroCommand*>(histories.top());
    ASSERT_TRUE(level_one_macro);
    std::vector<Command*> commands = level_one_macro->getCommands();
    ASSERT_EQ(2, commands.size());
    ASSERT_EQ(child_command_1_, commands.at(0));
    {
      auto* level_two_macro = dynamic_cast<MacroCommand*>(commands.at(1));
      commands = level_two_macro->getCommands();
      ASSERT_EQ(2, commands.size());
      ASSERT_EQ(child_command_2_, commands.at(0));
      ASSERT_EQ(child_command_3_, commands.at(1));
    }
  }
}

TEST(CommandHistoryTest, UndoShouldUndoTheLatestCommandRemoveItFromHistory) {
  auto* child_command_1_ = new MockCommand{};
  auto* child_command_2_ = new MockCommand{};
  CommandHistory history{};

  history.beginMacroCommand();
  history.addCommand(child_command_1_);
  history.endMacroCommand();
  history.addCommand(child_command_2_);

  history.undo();
  ASSERT_TRUE(child_command_2_->isUndoCalled());
  ASSERT_EQ(1, history.getHistory().size());

  history.undo();
  ASSERT_TRUE(child_command_1_->isUndoCalled());
  ASSERT_TRUE(history.getHistory().empty());
}
