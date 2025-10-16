#include "../include/CommandManager.hpp"
#include <iostream>

namespace vextra {

void CommandManager::registerCommand(std::unique_ptr<Command> command) {
    std::string_view name = command->getName();
    commands.emplace(name, std::move(command));
}

void CommandManager::execute(const std::vector<std::string_view>& args) {
    if (args.empty()) {
        std::cerr << ICON_ERROR << " No command provided.\n";
        listCommands();
        return;
    }

    std::string_view commandName = args[0];
    auto it = commands.find(commandName);

    if (it == commands.end()) {
        std::cerr << ICON_ERROR << " Unknown command: " << commandName << "\n";
        std::cout << "💡 Try `" << APP_NAME << " help` for a list of commands.\n";
        return;
    }

    // Slice args to exclude the command name itself
    std::vector<std::string_view> subArgs(args.begin() + 1, args.end());
    it->second->execute(subArgs);
}

void CommandManager::listCommands() const {
    std::cout << "📚 Available commands:\n";
    for (const auto& [name, cmd] : commands) {
        std::cout << "  🔹 " << name << " — " << cmd->getDescription() << "\n";
    }
}

} // namespace vextra
