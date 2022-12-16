#ifndef SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_
#define SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_

#include <stack>

#include "command.h"
#include "macro_command.h"

class CommandHistory {
 public:
  CommandHistory() = default;

  CommandHistory(const CommandHistory& other) =
      delete; /* TODO: need polymorphic cloning support */

  CommandHistory& operator=(const CommandHistory& other) =
      delete; /* TODO: need polymorphic cloning support */

  ~CommandHistory() {
    DeleteStackOf_(undid_histories_);
    DeleteStackOf_(histories_);
  }

  /**
   * @brief Begins the construction of a MacroCommand. All future commands will
   * be added into the MacroCommand until endMacroCommand is called.
   * @note If this begins a non-composite MacroCommand, the MacroCommand is
   * immediately added to the history and will be modified along with the
   * construction.
   */
  void beginMacroCommand() {
    auto* macro = new MacroCommand{};
    if (!IsConstructingMacro_()) {
      histories_.push(macro);
    }
    macros_under_construction_.push(macro);
  }

  /** @brief Takes the ownership of the commands. */
  void addCommand(Command* const command) {
    if (!IsConstructingMacro_()) {
      histories_.push(command);
    } else {
      auto* macro = macros_under_construction_.top();
      macro->addCommand(command);
    }
  }

  void endMacroCommand() {
    auto* macro = macros_under_construction_.top();
    macros_under_construction_.pop();
    if (IsConstructingMacro_()) {
      auto* parent = macros_under_construction_.top();
      parent->addCommand(macro);
    }
  }

  /** @brief Undoes the latest history. */
  void undo() {
    /* In order to test the CommandHistory, the popped command should be placed
      in another container, say another stack, and be deleted in the
      destructor. */
    Command* const latest = histories_.top();
    histories_.pop();
    latest->undo();
    undid_histories_.push(latest);
  }

  std::stack<Command*> getHistory() const {
    return histories_;
  }

 private:
  std::stack<Command*> histories_{};
  std::stack<Command*> undid_histories_{};

  /* All macros under construction are already added to histories.
    Be careful no to double free. */
  std::stack<MacroCommand*> macros_under_construction_{};

  bool IsConstructingMacro_() const {
    return !macros_under_construction_.empty();
  }

  template <typename T>
  void DeleteStackOf_(std::stack<T*>& targets) {
    while (!targets.empty()) {
      delete targets.top();
      targets.pop();
    }
  }
};

#endif /* end of include guard: \
          SRC_GRAPHICS_DRAG_AND_DROP_COMMAND_COMMAND_HISTORY_H_ */
