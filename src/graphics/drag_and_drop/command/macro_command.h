#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_

#include "command.h"

class MacroCommand : public Command {
 public:
  MacroCommand() {}
  ~MacroCommand() {}

  void execute() override {}

  void addCommand(Command* command) override {}

  void undo() override {}

  std::vector<Command*> getCommands() override {}
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_ */
