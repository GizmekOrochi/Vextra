#include "../include/CommandManager.hpp"
#include <iostream>
#include <iomanip> 
using namespace vextra;

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    std::string name(command->getName());
    commands.emplace(name, std::move(command));
}

void CommandManager::execute(const std::vector<std::string_view>& args) {
    if (args.empty()) {
        std::cerr << ICON_WARNING << " No command provided.\n";
        listCommands();
        std::cout << "\n💡 Tip: Use `" << APP_NAME << " help <command>` for more info.\n";
        return;
    }

    std::string_view commandName = args[0];
    auto it = commands.find(std::string(commandName));

    if (it == commands.end()) {
        std::cerr << ICON_ERROR << " Unknown command: " << commandName << "\n";
        std::cout << "💡 Try `" << APP_NAME << " help` for a list of commands.\n";
        return;
    }

    // Execute command with subarguments
    std::vector<std::string_view> subArgs(args.begin() + 1, args.end());
    it->second->execute(subArgs);
}

void CommandManager::listCommands() const {
    std::cout << "📚 Available commands:\n\n";
    for (const auto& [name, cmd] : commands) {
        std::cout << "  🔹 " << std::left << std::setw(10) << name
                  << " — " << cmd->getShortDescription() << "\n";
    }
}
