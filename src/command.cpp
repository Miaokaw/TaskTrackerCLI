//
// Created by msuperhero on 2025/7/3.
//

#include "command.h"
#include "task.h"

#include <iostream>
#include <ranges>


void loadCommands() {
    auto help = new Command(
        "help",
        "Display this help message",
        0,
        [](int argc, char *argv[]) {
            std::cout << "Available commands:\n";
            for (const auto &command: std::ranges::views::values(Command::commands)) {
                std::cout << command << "\n";
            }
        });

    auto add = new Command(
        "add",
        "Add a new item",
        1,
        [](int argc, char *argv[]) {
            auto newTask = new Task(argv[2]);
        });

    auto del = new Command(
        "delete",
        "delete a task",
        1,
        [](int argc, char *argv[]) {
            std::cout << "Deleting task with ID: " << argv[2] << std::endl;
            Task::del(*argv[2] - 48);
        });

    auto list = new Command(
        "list",
        "list all tasks",
        -1,
        [](int argc, char *argv[]) {
            if (argc == 0)
                Task::list();
            else if (argc == 1)
                Task::list(argv[2]);
        });

    auto update = new Command(
        "update",
        "update a task",
        2,
        [](int argc, char *argv[]) {
            Task::update(*argv[2] - 48, argv[3]);
        });

    auto markToDo = new Command(
        "mark-todo",
        "mark a task as todo",
        1,
        [](int argc, char *argv[]) {
            Task::mark(*argv[2] - 48, "todo");
        });

    auto markInProgress = new Command(
        "mark-in-progress",
        "mark a task as in-progress",
        1,
        [](int argc, char *argv[]) {
            Task::mark(*argv[2] - 48, "in-progress");
        });
    auto markDone = new Command(
        "mark-done",
        "mark a task as done",
        1,
        [](int argc, char *argv[]) {
            Task::mark(*argv[2] - 48, "done");
        }
    );
};
