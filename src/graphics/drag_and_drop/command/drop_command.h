#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class DropCommand : public Command {
 public:
  DropCommand(DragAndDrop* drag_and_drop, CommandHistory* command_history) {}
  DropCommand(const DropCommand& drop_command) {}

  void execute() override {}

  void undo() override {}

  double getX() const {}

  double getY() const {}
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_ */
