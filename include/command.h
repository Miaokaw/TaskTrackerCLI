//
// Created by msuperhero on 2025/7/3.
//

#ifndef COMMAND_H
#define COMMAND_H


#include <iostream>
#include <string_view>
#include <unordered_map>
#include <functional>

class Command
{
public:
    inline static std::unordered_map<std::string_view, Command> commands;
    const int argc;
    void (*execute)(int argc, char* args[]);

    Command(
        const std::string_view name,
        const std::string_view description,
        const int argc,
        void (*execute)(int argc, char* args[])
    )
        : argc(argc), execute(execute), name(name), description(description)
    {
        if (commands.contains(name))
            throw std::logic_error("Command already exists");

        commands.insert({name, *this});
    }

    [[nodiscard]]
    size_t hash() const
    {
        return std::hash<std::string_view>()(name);
    }

    friend std::ostream& operator<<(std::ostream& os, const Command& command)
    {
        os << command.name << ": " << command.description;
        return os;
    }

    [[nodiscard]]
    bool operator==(const Command& command) const
    {
        return name == command.name;
    }

private:
    const std::string_view name;
    const std::string_view description;
};


void loadCommands();

#endif //COMMAND_H
