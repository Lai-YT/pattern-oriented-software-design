#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_

#include <stack>

#include "command.h"
#include "macro_command.h"

class CommandHistory {
 public:
  ~CommandHistory() {}

  void beginMacroCommand() {
    macros_under_construction_.push(new MacroCommand{});
  }

  void addCommand(Command* command) {}

  void endMacroCommand() {
    histories_.push(macros_under_construction_.top());
    macros_under_construction_.pop();
  }

  void undo() {}

  std::stack<Command*> getHistory() const {
    return histories_;
  }

 private:
  std::stack<Command*> histories_{};
  std::stack<MacroCommand*> macros_under_construction_{};
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_ */
