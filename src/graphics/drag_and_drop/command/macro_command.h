#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_

#include "command.h"

class MacroCommand : public Command {
 public:
  MacroCommand() = default;

  ~MacroCommand() {
    for (auto* command : commands_) {
      delete command;
    }
  }

  /**
   * @brief Executes all commands contained by the MacroCommand in the order of
   * the are added.
   */
  void execute() override {
    for (auto* command : commands_) {
      command->execute();
    }
  }

  /** @brief Takes the ownership of the commands. */
  void addCommand(Command* const command) override {
    commands_.push_back(command);
  }

  void undo() override {}

  std::vector<Command*> getCommands() override {}

 private:
  std::vector<Command*> commands_{};
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_ */
