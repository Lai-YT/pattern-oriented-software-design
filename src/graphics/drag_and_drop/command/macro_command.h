#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_

#include "command.h"

class MacroCommand : public Command {
 public:
  MacroCommand() = default;

  MacroCommand(const MacroCommand& other) =
      delete; /* TODO: need polymorphic cloning support */

  MacroCommand& operator=(const MacroCommand& other) =
      delete; /* TODO: need polymorphic cloning support */

  ~MacroCommand() {
    for (auto* command : commands_) {
      delete command;
    }
  }

  /**
   * @brief Executes all commands contained by the MacroCommand in the order of
   * they are added.
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

  /**
   * @brief Undoes all commands contained by the MacroCommand in the reversed
   * order of they are added.
   */
  void undo() override {
    for (auto itr = commands_.rbegin(); itr != commands_.rend(); itr++) {
      (*itr)->undo();
    }
  }

  /**
   * @brief Returns all first level commands contained by the MacroCommand in
   * the order of they are added.
   *
   * @note you should not delete the commands since the ownership are kept by
   * the MacroCommand.
   */
  std::vector<Command*> getCommands() override {
    return commands_;
  }

 private:
  std::vector<Command*> commands_{};
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_MACRO_COMMAND_H_ */
