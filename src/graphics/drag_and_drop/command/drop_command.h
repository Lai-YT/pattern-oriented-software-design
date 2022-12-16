#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class DropCommand : public Command {
 public:
  DropCommand(DragAndDrop* const drag_and_drop,
              CommandHistory* const command_history)
      : drag_and_drop_{drag_and_drop}, command_history_{command_history} {}

  DropCommand(const DropCommand& drop_command) =
      default; /* shallow copy is allowed since the pointers are shared */

  void execute() override {
    auto* curr_mouse_pos = MousePosition::getInstance();
    drag_and_drop_->drop(curr_mouse_pos->getX(), curr_mouse_pos->getY());

    /* so undo-able */
    was_executed_ = true;
    RecordPosition_(*curr_mouse_pos);
    command_history_->addCommand(new DropCommand{*this});
  }

  void undo() override {
    if (was_executed_) {
      drag_and_drop_->grab(dropped_x_, dropped_y_);
    }
  }

  double getX() const {
    return dropped_x_;
  }

  double getY() const {
    return dropped_y_;
  }

 private:
  DragAndDrop* drag_and_drop_;
  CommandHistory* command_history_;

  /* states for undo */
  bool was_executed_ = false;
  /* dropped x and y are meaningless unless was executed */
  double dropped_x_ = 0;
  double dropped_y_ = 0;

  /**
   * @note Can't be const-reference since the getters of MousePosition are
   * surprisingly non-const.
   */
  void RecordPosition_(MousePosition& dropped_pos) {
    dropped_x_ = dropped_pos.getX();
    dropped_y_ = dropped_pos.getY();
  }
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_DROP_COMMAND_H_ */
