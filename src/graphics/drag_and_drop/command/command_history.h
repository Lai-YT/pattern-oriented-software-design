#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_

#include <stack>

#include "command.h"

class CommandHistory {
 public:
  CommandHistory() {}
  ~CommandHistory() {}

  void beginMacroCommand() {}

  void addCommand(Command* command) {}

  void endMacroCommand() {}

  void undo() {}

  std::stack<Command*> getHistory() {}
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_ */
