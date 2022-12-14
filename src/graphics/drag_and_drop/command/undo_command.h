#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class UndoCommand : public Command {
 public:
  UndoCommand(DragAndDrop* drag_and_drop, CommandHistory* command_history) {}

  void execute() override {}

  void undo() override {}
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_UNDO_COMMAND_H_ */
