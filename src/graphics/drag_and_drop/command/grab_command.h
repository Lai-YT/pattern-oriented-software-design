#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class GrabCommand : public Command {
 public:
  GrabCommand(DragAndDrop* drag_and_drop, CommandHistory* command_history) {}
  GrabCommand(const GrabCommand& grab_command) {}

  void execute() override {}

  void undo() override {}

  double getX() const {}

  double getY() const {}
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_ */
