#pragma once
#include "Command.hpp"
#include "Config.hpp"
#include <string_view>
#include <filesystem>

namespace vextra {

/**
 * @class CreateCommand
 * @brief Implements the `vextra create` command.
 *
 * The `CreateCommand` class is responsible for generating a new project
 * structure with standard directories and starter files.
 *
 * ## Responsibilities
 * - Parse the command arguments (`vextra create <ProjectName> [-cpp | -c | -java]`).
 * - Validate that the target directory does not already exist.
 * - Generate a consistent folder hierarchy.
 * - Write default boilerplate files (README, Makefile, .gitignore, etc.).
 *
 * ## Supported language templates
 * - `-cpp` → C++ project with `main.cpp` and adapted Makefile.
 * - `-c` → C project with `main.c` and adapted Makefile.
 * - `-java` → Java project with `Main.java` and simple Makefile.
 * - *(none)* → Neutral project with an empty structure and placeholder.
 *
 * ## Example usage
 * ```bash
 * vextra create MyProject
 * vextra create MyProject -cpp
 * vextra create MyProject -java
 * ```
 *
 * ## Notes
 * - All directory and file names are defined in `Config.hpp`.
 * - Errors and success messages use standardized icons and messages.
 */
class CreateCommand : public Command {
public:
    /**
     * @brief Get the command name ("create").
     * @return The command identifier used by CommandManager.
     */
    std::string_view getName() const noexcept override { return "create"; }

    /**
     * @brief Get a short description of the command.
     * @return A human-readable summary for `vextra help`.
     */
    std::string_view getDescription() const noexcept override { return "Create a new project structure"; }

    /**
     * @brief Execute the command with the provided CLI arguments.
     * @param args Command-line arguments excluding the command name itself.
     */
    void execute(const std::vector<std::string_view>& args) override;

private:
    /**
     * @brief Create the standard directory structure for a new project.
     * @param name The name of the new project.
     */
    void createProjectStructure(const std::string& name);

    /**
     * @brief Generate boilerplate files like README.md, Makefile, and .gitignore.
     * @param name The project name.
     * @param language Optional language flag (-cpp, -c, -java, etc.).
     */
    void createBaseFiles(const std::string& name, std::string_view language);

    /**
     * @brief Utility function to safely write content to a file.
     * @param path Full path of the file to create.
     * @param content File contents to write.
     * @throws std::runtime_error if the file cannot be created.
     */
    void createFile(const std::filesystem::path& path, const std::string& content);
};

} // namespace vextra
