#pragma once
#include <string_view>
#include <vector>

/**
 * @class Command
 * @brief Abstract base class for all Vextra CLI commands.
 *
 * Each subclass represents a single CLI command (e.g. `create`, `help`, `build`).
 *
 * ## Design overview
 * - Implements the **Command Pattern**, allowing dynamic registration and execution.
 * - Uses `std::string_view` for lightweight command identifiers and descriptions.
 * - Supports both short and detailed help text.
 *
 * ## Usage example
 * ```cpp
 * class CreateCommand : public Command {
 * public:
 *     std::string_view getName() const noexcept override { return "create"; }
 *     std::string_view getShortDescription() const noexcept override { return "Create a new project structure."; }
 *     std::string_view getDetailedDescription() const noexcept override { return "Usage:\n  vextra create <ProjectName> ..."; }
 *     void execute(const std::vector<std::string_view>& args) override { ... }
 * };
 * ```
 */
class Command {
public:
    virtual ~Command() = default;

    /// @brief Returns the unique name of the command (used in CLI dispatch).
    virtual std::string_view getName() const noexcept = 0;

    /// @brief Returns a one-line summary of what this command does.
    virtual std::string_view getShortDescription() const noexcept = 0;

    /// @brief Returns detailed help text (usage, flags, examples...).
    virtual std::string_view getDetailedDescription() const noexcept = 0;

    /// @brief Executes the command logic with given arguments.
    virtual void execute(const std::vector<std::string_view>& args) = 0;
};
