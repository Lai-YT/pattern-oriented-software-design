#include <gtest/gtest.h>

#include <stack>
#include <vector>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class DropCommandTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  MockDragAndDrop mock_drag_and_drop_{};
  CommandHistory history_{};
  DropCommand drop_command_{&mock_drag_and_drop_, &history_};
};

TEST_F(DropCommandTest, ExecuteShouldCallDropWithCurrentMousePosition) {
  const double curr_x = 85.23;
  const double curr_y = 232.7;
  MousePosition::getInstance()->setPos(curr_x, curr_y);

  drop_command_.execute();

  ASSERT_NEAR(curr_x, mock_drag_and_drop_.getDropX(), DELTA);
  ASSERT_NEAR(curr_y, mock_drag_and_drop_.getDropY(), DELTA);
}

TEST_F(DropCommandTest, UndoWithoutPreCalledExecuteShouldHaveNoEffect) {
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in MockDragAndDrop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);

  drop_command_.undo();

  auto* curr_pos = MousePosition::getInstance();
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getDropX(), DELTA);
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getDropY(), DELTA);
}

TEST_F(DropCommandTest, UndoShouldCallGrabWithWhereWasDropped) {
  const double dropped_x = 10;
  const double dropped_y = 20;
  MousePosition::getInstance()->setPos(dropped_x, dropped_y);
  /* to undo, you have to execute first */
  drop_command_.execute();

  drop_command_.undo();

  ASSERT_NEAR(dropped_x, mock_drag_and_drop_.getGrabX(), DELTA);
  ASSERT_NEAR(dropped_y, mock_drag_and_drop_.getGrabY(), DELTA);
}

TEST_F(DropCommandTest,
       GetXAndYShouldReturnThePositionWhereTheCommandWasExecuted) {
  const double executed_x = 10;
  const double executed_y = 20;
  MousePosition::getInstance()->setPos(executed_x, executed_y);
  drop_command_.execute();

  const double got_x = drop_command_.getX();
  const double got_y = drop_command_.getY();

  ASSERT_NEAR(executed_x, got_x, DELTA);
  ASSERT_NEAR(executed_y, got_y, DELTA);
}

TEST_F(DropCommandTest, ExecuteShouldCopyItselfIntoHistoryAndEndMacro) {
  const double executed_x = 10;
  const double executed_y = 20;
  MousePosition::getInstance()->setPos(executed_x, executed_y);

  /* History:
   *  Macro {
   *    Drop
   *  }  // ended by drop
   *  Mock
   */
  history_.beginMacroCommand();
  drop_command_.execute();
  /* The MockCommand added after execute is critical. If endMacroCommand isn't
    called, the MockCommand will be inside the macro. */
  history_.addCommand(new MockCommand{});

  std::stack<Command*> histories = history_.getHistory();
  ASSERT_EQ(2, histories.size());
  auto* mock = dynamic_cast<MockCommand*>(histories.top());
  ASSERT_TRUE(mock);
  histories.pop();
  { /* make the feeling of levels with block */
    auto* macro = dynamic_cast<MacroCommand*>(histories.top());
    ASSERT_TRUE(macro);
    const std::vector<Command*> latest_commands = macro->getCommands();
    ASSERT_EQ(1, latest_commands.size());
    auto* latest = dynamic_cast<DropCommand*>(latest_commands.at(0));
    ASSERT_NEAR(executed_x, latest->getX(), DELTA);
    ASSERT_NEAR(executed_y, latest->getY(), DELTA);
  }
}

TEST_F(DropCommandTest, AddCommandShouldThrowException) {
  auto command = MockCommand{};

  ASSERT_ANY_THROW({ drop_command_.addCommand(&command); });
}

TEST_F(DropCommandTest, GetCommandsShouldThrowException) {
  ASSERT_ANY_THROW({ drop_command_.getCommands(); });
}
