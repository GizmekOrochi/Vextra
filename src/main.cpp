#include "../include/CommandManager.hpp"
#include "../include/command/CreateCommand.hpp"
#include <iostream>

using namespace vextra;

int main(int argc, char* argv[]) {
    CommandManager manager;
    manager.registerCommand(std::make_unique<CreateCommand>());

    if (argc < 2) {
        std::cerr << ICON_WARNING << " No command provided.\n";
        manager.listCommands();
        return 1;
    }

    std::vector<std::string_view> args(argv + 1, argv + argc);
    manager.execute(args);
    return 0;
}
