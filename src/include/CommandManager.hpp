#pragma once
#include "command/Command.hpp"
#include "Config.hpp"
#include <memory>
#include <unordered_map>
#include <string_view>
#include <vector>

namespace vextra {

/**
 * @class CommandManager
 * @brief Central command dispatcher for the Vextra CLI tool.
 *
 * ## Overview
 * The `CommandManager` class manages registration, lookup, and execution
 * of all CLI commands supported by Vextra.
 *
 * It acts as the “brain” of the command system:
 * - Stores all available `Command` instances.
 * - Matches user input (e.g., `vextra create`) to the corresponding command.
 * - Provides error handling and fallback behavior for unknown commands.
 *
 * ## Design goals
 * - Fully extensible: add new commands dynamically.
 * - Efficient lookups via `std::unordered_map`.
 * - Consistent command discovery for a potential `help` command.
 *
 * ## Example
 * ```cpp
 * CommandManager manager;
 * manager.registerCommand(std::make_unique<CreateCommand>());
 * manager.execute({"create", "MyProject", "-cpp"});
 * ```
 */
class CommandManager {
public:
    /**
     * @brief Registers a new command instance.
     * @param command A unique pointer to a command implementation.
     *
     * Example:
     * ```cpp
     * manager.registerCommand(std::make_unique<CreateCommand>());
     * ```
     */
    void registerCommand(std::unique_ptr<Command> command);

    /**
     * @brief Executes the command corresponding to user input.
     * @param args The command-line arguments (e.g., from `argv`).
     *
     * Automatically detects the command name (`args[0]`) and forwards
     * the rest to the appropriate `Command::execute()` method.
     */
    void execute(const std::vector<std::string_view>& args);

    /**
     * @brief Prints a list of all registered commands and their descriptions.
     * Useful for implementing `vextra help`.
     */
    void listCommands() const;

private:
    std::unordered_map<std::string_view, std::unique_ptr<Command>> commands;
};

} // namespace vextra
