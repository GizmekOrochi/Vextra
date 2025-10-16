#include "../include/command/HelpCommand.hpp"
#include "../include/Config.hpp"
#include <iostream>
#include <iomanip>

using namespace vextra;

HelpCommand::HelpCommand(const CommandManager& manager)
    : manager(manager) {}

void HelpCommand::execute(const std::vector<std::string_view>& args) {
    if (args.empty()) {
        std::cout << "📚 Available commands:\n\n";
        for (const auto& [name, cmd] : manager.getCommands()) {
            std::cout << "  🔹 " << std::left << std::setw(10) << name
                      << " — " << cmd->getShortDescription() << "\n";
        }
        std::cout << "\n💡 Use '" << APP_NAME << " help <command>' for detailed information.\n";
        return;
    }

    std::string_view target = args[0];
    Command* cmd = manager.findCommand(target);
    if (!cmd) {
        std::cerr << "❌ Unknown command: " << target << "\n";
        return;
    }

    std::cout << "🧩 Help for command: " << target << "\n";
    std::cout << cmd->getDetailedDescription() << "\n";
}
