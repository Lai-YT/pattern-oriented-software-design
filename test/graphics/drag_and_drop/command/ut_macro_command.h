#include <gtest/gtest.h>

#include <vector>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

/* TODO: how do I test the order which the child commands are executed? */

class MacroCommandTest : public testing::Test {
 protected:
  MacroCommandTest() {
    child_macro_command_->addCommand(child_command_2_);
    child_macro_command_->addCommand(child_command_3_);
    macro_command_.addCommand(child_command_1_);
    macro_command_.addCommand(child_macro_command_);
    macro_command_.addCommand(child_command_4_);
  }
  /* create child commands */
  MockCommand* child_command_1_ = new MockCommand{};
  MockCommand* child_command_2_ = new MockCommand{};
  MockCommand* child_command_3_ = new MockCommand{};
  MacroCommand* child_macro_command_ = new MacroCommand{};
  MockCommand* child_command_4_ = new MockCommand{};

  /* create the test target */
  MacroCommand macro_command_{};
};

TEST_F(MacroCommandTest, ExecuteShouldExecuteAllChildCommands) {
  macro_command_.execute();

  ASSERT_TRUE(child_command_1_->isExecuteCalled());
  ASSERT_TRUE(child_command_2_->isExecuteCalled());
  ASSERT_TRUE(child_command_3_->isExecuteCalled());
  ASSERT_TRUE(child_command_4_->isExecuteCalled());
}

TEST_F(MacroCommandTest, UndoShouldUndoAllChildCommands) {
  macro_command_.undo();

  ASSERT_TRUE(child_command_1_->isUndoCalled());
  ASSERT_TRUE(child_command_2_->isUndoCalled());
  ASSERT_TRUE(child_command_3_->isUndoCalled());
  ASSERT_TRUE(child_command_4_->isUndoCalled());
}

TEST_F(MacroCommandTest,
       GetCommandsShouldReturnFirstLevelChildCommandsInTheOrderTheyAreAdded) {
  const std::vector<Command*> commands = macro_command_.getCommands();

  ASSERT_EQ(3, commands.size());
  ASSERT_EQ(child_command_1_, commands.at(0));
  ASSERT_EQ(child_macro_command_, commands.at(1));
  ASSERT_EQ(child_command_4_, commands.at(2));
}
