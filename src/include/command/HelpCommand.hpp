#pragma once
#include "Command.hpp"
#include "CommandManager.hpp"
#include <string_view>

/**
 * @class HelpCommand
 * @brief Implements the `vextra help` command.
 *
 * Provides contextual help for all registered commands.
 * 
 * ## Behaviors
 * - `vextra help` → lists all commands with a short description.
 * - `vextra help <command>` → displays detailed help text for that specific command.
 *
 * ## Example
 * ```bash
 * vextra help
 * vextra help create
 * ```
 *
 * ## Design note
 * The HelpCommand holds a reference to the CommandManager
 * so it can query all known commands and their descriptions.
 */
class HelpCommand : public Command {
public:
    explicit HelpCommand(const CommandManager& manager);

    std::string_view getName() const noexcept override { return "help"; }

    std::string_view getShortDescription() const noexcept override {
        return "Show usage information about available commands.";
    }

    std::string_view getDetailedDescription() const noexcept override {
        return R"(
Usage:
  vextra help [command]

Description:
  Without arguments, lists all available commands.
  With a command name, displays detailed usage and examples for that command.

Examples:
  vextra help
  vextra help create
)";
    }

    void execute(const std::vector<std::string_view>& args) override;

private:
    const CommandManager& manager;
};
