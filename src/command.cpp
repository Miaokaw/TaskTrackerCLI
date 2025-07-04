//
// Created by msuperhero on 2025/7/3.
//

#include "command.h"
#include "task.h"

#include <iostream>
#include <ranges>


void loadCommands()
{
    auto help = Command("help",
                        "Display this help message",
                        0,
                        [](int argc, char* argv[])
                        {
                            std::cout << "Available commands:\n";
                            for (const auto& command : std::ranges::views::values(Command::commands))
                            {
                                std::cout << command << "\n";
                            }
                        });

    auto add = Command("add",
                       "Add a new item",
                       1,
                       [](int argc, char* argv[])
                       {

                           std::cout << "Task added successfully (ID:" << 1 << ")" << "\n";
                       });
};
