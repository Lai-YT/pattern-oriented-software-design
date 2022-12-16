#include <gtest/gtest.h>

#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/move_command.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class MoveCommandTest : public testing::Test {
 protected:
  const double DELTA = 0.001;

  MockDragAndDrop mock_drag_and_drop_{};
  CommandHistory history_{};
  MoveCommand move_command_{&mock_drag_and_drop_, &history_};
};

TEST_F(MoveCommandTest, ExecuteShouldCallMoveWithCurrentMousePosition) {
  const double curr_x = 85.23;
  const double curr_y = 232.7;
  MousePosition::getInstance()->setPos(curr_x, curr_y);

  move_command_.execute();

  ASSERT_NEAR(curr_x, mock_drag_and_drop_.getMoveX(), DELTA);
  ASSERT_NEAR(curr_y, mock_drag_and_drop_.getMoveY(), DELTA);
}

TEST_F(MoveCommandTest, UndoWithoutPreCalledExecuteShouldHaveNoEffect) {
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in MockDragAndDrop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);

  move_command_.undo();

  auto* curr_pos = MousePosition::getInstance();
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getMoveX(), DELTA);
  ASSERT_NEAR(NOT_CALLED, mock_drag_and_drop_.getMoveY(), DELTA);
}

TEST_F(MoveCommandTest, UndoShouldCallMoveWithPreviousMousePosition) {
  const double prev_x = 10;
  const double prev_y = 20;
  const double NOT_CALLED = 0; /* initial value used in MockDragAndDrop */
  MousePosition::getInstance()->setPos(prev_x, prev_y);
  /* to undo, you have to execute first */
  move_command_.execute();
  mock_drag_and_drop_.move(NOT_CALLED, NOT_CALLED); /* clear */

  move_command_.undo();

  ASSERT_NEAR(prev_x, mock_drag_and_drop_.getMoveX(), DELTA);
  ASSERT_NEAR(prev_y, mock_drag_and_drop_.getMoveY(), DELTA);
}

TEST_F(MoveCommandTest,
       GetXAndYShouldReturnThePositionWhereTheCommandWasExecuted) {
  const double executed_x = 10;
  const double executed_y = 20;
  MousePosition::getInstance()->setPos(executed_x, executed_y);
  move_command_.execute();

  const double got_x = move_command_.getX();
  const double got_y = move_command_.getY();

  ASSERT_NEAR(executed_x, got_x, DELTA);
  ASSERT_NEAR(executed_y, got_y, DELTA);
}

TEST_F(MoveCommandTest, ShouldCopyItselfIntoTheHistoryAfterExecution) {
  const double executed_x = 10;
  const double executed_y = 20;
  MousePosition::getInstance()->setPos(executed_x, executed_y);

  move_command_.execute();

  const std::stack<Command*> histories = history_.getHistory();
  ASSERT_EQ(1, histories.size());
  auto* latest_command = dynamic_cast<MoveCommand*>(histories.top());
  ASSERT_TRUE(latest_command);
  ASSERT_NEAR(executed_x, latest_command->getX(), DELTA);
  ASSERT_NEAR(executed_y, latest_command->getY(), DELTA);
}

TEST_F(MoveCommandTest, AddCommandShouldThrowException) {
  auto command = MockCommand{};

  ASSERT_ANY_THROW({ move_command_.addCommand(&command); });
}

TEST_F(MoveCommandTest, GetCommandsShouldThrowException) {
  ASSERT_ANY_THROW({ move_command_.getCommands(); });
}
