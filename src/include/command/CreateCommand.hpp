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
 * The `CreateCommand` is responsible for generating a new project structure
 * with standardized folders, a Makefile adapted to the chosen language,
 * and basic boilerplate files.
 *
 * ## Features
 * - Creates directories for `src`, `include`, `core`, `bin`, `doc`, etc.
 * - Supports language templates:
 *   - `-cpp` → C++ project (`main.cpp`, Makefile for g++).
 *   - `-c`   → C project (`main.c`, Makefile for gcc).
 *   - `-java` → Java project (`Main.java`, Makefile for javac).
 *   - *(none)* → Empty template with placeholders.
 * - Automatically generates:
 *   - `README.md`
 *   - `.gitignore`
 *   - `.<ProjectName>-Info` metadata file
 *
 * ## Example usage
 * ```bash
 * vextra create MyProject
 * vextra create MyProject -cpp
 * vextra create MyProject -java
 * ```
 */
class CreateCommand : public Command {
public:
    /// @brief Command name (for CLI dispatch).
    std::string_view getName() const noexcept override { return "create"; }

    /// @brief Short one-line description for `vextra help`.
    std::string_view getShortDescription() const noexcept override {
        return "Create a new project structure.";
    }

    /// @brief Detailed description for `vextra help create`.
    std::string_view getDetailedDescription() const noexcept override {
        return R"(
Usage:
  vextra create <ProjectName> [options]

Options:
  -cpp   Create a C++ project structure (main.cpp, Makefile for g++).
  -c     Create a C project structure (main.c, Makefile for gcc).
  -java  Create a Java project structure (Main.java, Makefile for javac).

Example:
  vextra create MyApp -cpp

Description:
  Generates a complete project folder hierarchy with standard directories
  (src/, include/, bin/, doc/, etc.) and minimal boilerplate files.
)";
    }

    /// @brief Executes the `vextra create` command.
    void execute(const std::vector<std::string_view>& args) override;

private:
    void createProjectStructure(const std::string& name);
    void createBaseFiles(const std::string& name, std::string_view language);
    void createFile(const std::filesystem::path& path, const std::string& content);
};

} // namespace vextra
