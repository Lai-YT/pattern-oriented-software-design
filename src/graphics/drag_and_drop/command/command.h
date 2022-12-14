#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_H_

#include <vector>

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual void addCommand(Command* command) {
    throw "cannot add command.";
  }
  virtual std::vector<Command*> getCommands() {
    throw "cannot get commands.";
  }
};

#endif /* end of include guard: SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_H_ \
        */
