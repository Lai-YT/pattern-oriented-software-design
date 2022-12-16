#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class UndoCommand : public Command {
 public:
  UndoCommand(DragAndDrop* drag_and_drop, CommandHistory* command_history)
      : history_{command_history} {}

  void execute() override {
    history_->undo();
  }

  /** @brief Does nothing. UndoCommand is solely used to handle the event. */
  void undo() override {}

 private:
  CommandHistory* history_;
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_ */
