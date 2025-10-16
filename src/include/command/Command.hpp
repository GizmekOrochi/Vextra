#pragma once
#include <string_view>
#include <vector>

/**
 * @class Command
 * @brief Abstract base class for all Vextra CLI commands.
 *
 * This class defines the unified interface for every command
 * that the Vextra CLI tool can execute (e.g. `create`, `build`, `help`).
 *
 * ## Design goals
 * - Avoid string copies by using `std::string_view` for lightweight command identifiers.
 * - Provide a consistent, extensible command interface.
 * - Enable dynamic command registration and dispatching via `CommandManager`.
 *
 * ## Pattern
 * Implements the **Command Pattern**, where each subclass encapsulates
 * a specific operation and can be executed interchangeably.
 */
class Command {
public:
    virtual ~Command() = default;

    /**
     * @brief Returns the name of the command (used to trigger it in the CLI).
     * Example: `"create"`, `"build"`, `"help"`.
     */
    virtual std::string_view getName() const noexcept = 0;

    /**
     * @brief Returns a short human-readable description of the command.
     * Example: `"Creates a new project structure"`.
     */
    virtual std::string_view getDescription() const noexcept = 0;

    /**
     * @brief Executes the command with given CLI arguments.
     * @param args Command-line arguments excluding the binary name and command itself.
     */
    virtual void execute(const std::vector<std::string_view>& args) = 0;
};
