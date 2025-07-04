#include "command.h"
#include "task.h"

#include <iostream>

int main(const int argc, char* argv[])
{
    Task::readFromJson("./tasks.json");
    loadCommands();
    if (argc == 1)
    {
        std::cerr << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cerr << "Use --help for more information." << std::endl;
        return 1;
    }

    const auto it = Command::commands.find(argv[1]);
    const Command* command = Command::commands.end() != it ? &it->second : nullptr;
    if (command == nullptr)
    {
        std::cerr << "Unknown command: " << argv[1] << std::endl;
        std::cerr << "Use --help for a list of available commands." << std::endl;
        return 1;
    }

    if (command->argc != -1) {
        if (argc - 2 < command->argc)
        {
            std::cerr << "ERROR: Too few arguments." << std::endl;
            return 1;
        }
        if (argc - 2 > command->argc)
        {
            std::cerr << "ERROR: Too many arguments." << std::endl;
            return 1;
        }
    }

    try
    {
        command->execute(argc - 2, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
