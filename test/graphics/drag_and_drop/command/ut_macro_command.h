#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

/* TODO: how do I test the order which the child commands are executed? */

TEST(MacroCommandTest, ExecuteShouldExecuteAllChildCommands) {
  /* create child commands */
  auto* child_command_1 = new MockCommand{};
  auto* child_command_2 = new MockCommand{};
  auto* child_command_3 = new MockCommand{};
  auto* child_macro_command = new MacroCommand{};
  child_macro_command->addCommand(child_command_2);
  child_macro_command->addCommand(child_command_3);
  auto child_command_4 = new MockCommand{};
  /* create the test target */
  auto macro_command = MacroCommand{};
  macro_command.addCommand(child_command_1);
  macro_command.addCommand(child_macro_command);
  macro_command.addCommand(child_command_4);

  macro_command.execute();

  ASSERT_TRUE(child_command_1->isExecuteCalled());
  ASSERT_TRUE(child_command_2->isExecuteCalled());
  ASSERT_TRUE(child_command_3->isExecuteCalled());
  ASSERT_TRUE(child_command_4->isExecuteCalled());
}

TEST(MacroCommandTest, UndoShouldUndoAllChildCommands) {
  /* create child commands */
  auto* child_command_1 = new MockCommand{};
  auto* child_command_2 = new MockCommand{};
  auto* child_command_3 = new MockCommand{};
  auto* child_macro_command = new MacroCommand{};
  child_macro_command->addCommand(child_command_2);
  child_macro_command->addCommand(child_command_3);
  auto child_command_4 = new MockCommand{};
  /* create the test target */
  auto macro_command = MacroCommand{};
  macro_command.addCommand(child_command_1);
  macro_command.addCommand(child_macro_command);
  macro_command.addCommand(child_command_4);

  macro_command.undo();

  ASSERT_TRUE(child_command_1->isUndoCalled());
  ASSERT_TRUE(child_command_2->isUndoCalled());
  ASSERT_TRUE(child_command_3->isUndoCalled());
  ASSERT_TRUE(child_command_4->isUndoCalled());
}
