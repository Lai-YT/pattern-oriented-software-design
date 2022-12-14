#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class GrabCommand : public Command {
 public:
  GrabCommand(DragAndDrop* drag_and_drop, CommandHistory* command_history)
      : drag_and_drop_{drag_and_drop}, command_history_{command_history} {}

  GrabCommand(const GrabCommand& grab_command) =
      default; /* shallow copy is allowed since the pointers are shared */

  void execute() override {
    auto* curr_mouse_pos = MousePosition::getInstance();
    drag_and_drop_->grab(curr_mouse_pos->getX(), curr_mouse_pos->getY());
    was_executed_ = true;
    prev_x_ = curr_mouse_pos->getX();
    prev_y_ = curr_mouse_pos->getY();
  }

  void undo() override {
    if (was_executed_) {
      drag_and_drop_->move(prev_x_, prev_y_);
    }
  }

  double getX() const {}

  double getY() const {}

 private:
  DragAndDrop* drag_and_drop_;
  CommandHistory* command_history_;
  bool was_executed_ = false;
  /* previous x and y are meaningless unless was executed */
  double prev_x_ = 0;
  double prev_y_ = 0;
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_ */
