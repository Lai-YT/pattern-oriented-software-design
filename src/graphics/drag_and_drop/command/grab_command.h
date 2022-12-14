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
    /* so undo-able */
    was_executed_ = true;
    RecordPosition_();

    auto* curr_mouse_pos = MousePosition::getInstance();
    drag_and_drop_->grab(curr_mouse_pos->getX(), curr_mouse_pos->getY());
  }

  void undo() override {
    if (was_executed_) {
      drag_and_drop_->move(grabbed_x_, grabbed_y_);
    }
  }

  double getX() const {
    return grabbed_x_;
  }

  double getY() const {
    return grabbed_y_;
  }

 private:
  DragAndDrop* drag_and_drop_;
  CommandHistory* command_history_;

  /* states for undo */
  bool was_executed_ = false;
  /* grabbed x and y are meaningless unless was executed */
  double grabbed_x_ = 0;
  double grabbed_y_ = 0;

  void RecordPosition_() {
    auto* curr_mouse_pos = MousePosition::getInstance();
    grabbed_x_ = curr_mouse_pos->getX();
    grabbed_y_ = curr_mouse_pos->getY();
  }
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_GRAB_COMMAND_H_ */
