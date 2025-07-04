//
// Created by msuperhero on 2025/7/3.
//

#ifndef TASK_H
#define TASK_H
#include <string>
#include <string_view>
#include <chrono>
#include <iomanip>
#include <unordered_map>

class Task
{
public:
    enum Status
    {
        PENDING = 0,
        IN_PROGRESS = 1,
        COMPLETED = 2
    };

    static std::unordered_map<int, Task> tasks;

    explicit Task(const std::string_view description)
        : description(description), createdTime(std::time(nullptr))
    {

        for (int i = 0; ; i++)
        {
            // Generate a unique ID for the task
            id = i;
            break;
        }
        updatedTime = createdTime;
        tasks.insert({id,*this});
    }

    void update(const std::string_view newDescription)
    {
        description = newDescription;
        updatedTime = std::time(nullptr);
    }

    ~Task()
    {
        // del in json
    }

    void markStatus(const int newStatus)
    {
        status = newStatus;
    }

    bool operator==(const Task& task) const
    {
        return id == task.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Task& task)
    {
        os << task.description << std::endl;
        return os;
    }

    size_t hash() const
    {
        return std::hash<int>()(id);
    }

private:
    int id;
    std::string description;
    int status = PENDING; // 0: pending, 1: in progress, 2: completed
    const time_t createdTime;
    time_t updatedTime;
};


class Hasher
{
public:
    size_t operator()(const Task& task) const
    {
        return task.hash();
    }
};


#endif //TASK_H
