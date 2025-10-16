#include "CommandManager.hpp"
#include "command/CreateCommand.hpp"
#include "command/HelpCommand.hpp"

int main(int argc, char* argv[]) {
    using namespace vextra;

    CommandManager manager;
    manager.registerCommand(std::make_unique<CreateCommand>());
    manager.registerCommand(std::make_unique<HelpCommand>(manager));

    std::vector<std::string_view> args(argv + 1, argv + argc);
    manager.execute(args);

    return 0;
}
