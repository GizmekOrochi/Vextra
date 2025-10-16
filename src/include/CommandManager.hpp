#pragma once
#include "command/Command.hpp"
#include "Config.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <string_view>
#include <iostream>

/**
 * @class CommandManager
 * @brief Central registry and dispatcher for all CLI commands.
 *
 * This class manages command registration and execution.
 * It follows a simple design:
 * - Each command inherits from `Command`.
 * - Commands are registered dynamically using `registerCommand()`.
 * - `execute()` locates and runs the correct command based on CLI arguments.
 *
 * ## Responsibilities
 * - Maintain a registry of all available commands.
 * - Dispatch execution based on the first CLI argument.
 * - Provide listing and lookup utilities for the `help` command.
 *
 * ## Example
 * ```cpp
 * CommandManager manager;
 * manager.registerCommand(std::make_unique<CreateCommand>());
 * manager.registerCommand(std::make_unique<HelpCommand>(manager));
 * manager.execute({"create", "MyProject", "-cpp"});
 * ```
 */
class CommandManager {
public:
    /**
     * @brief Registers a new command into the manager.
     * @param command The command instance to register (ownership transferred).
     */
    void registerCommand(std::unique_ptr<Command> command);

    /**
     * @brief Executes a command based on CLI arguments.
     * @param args The command-line arguments excluding the binary name.
     */
    void execute(const std::vector<std::string_view>& args);

    /**
     * @brief Prints all available commands (used by default when no command is provided).
     */
    void listCommands() const;

    /**
     * @brief Returns a const reference to all registered commands.
     */
    const std::unordered_map<std::string, std::unique_ptr<Command>>& getCommands() const { return commands; }

    /**
     * @brief Finds a command by name.
     * @param name Command name (e.g. `"create"`, `"help"`).
     * @return Pointer to the command if found, otherwise nullptr.
     */
    Command* findCommand(std::string_view name) const {
        if (auto it = commands.find(std::string(name)); it != commands.end())
            return it->second.get();
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
};
