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
#include <iostream>
#include <cstring>

class Task {
public:
    inline static std::unordered_map<int, Task> tasks;

    static void readFromJson(const std::string &jsonFilePath);

    static void writeToJson(const std::string &jsonFilePath, const Task &newTask);

    static void list();
    static void list(const char * str);

    static void update(int id, std::string_view newDescription);

    static void mark(int id, std::string_view newStatus);

    static void del(int id);

    explicit Task(const std::string_view description)
        : description(description) {
        updateTime();
        createdTime = updatedTime;

        int i = 0;
        while (tasks.contains(i))
            ++i;
        id = i;
        tasks.insert({id, *this});
        std::cout << "Task created successfully (ID: " << id << ")" << std::endl;
        writeToJson("./tasks.json", *this);
    }

    Task(
        const int id,
        const std::string_view description,
        const std::string_view status,
        const std::string_view createdTime,
        const std::string_view updatedTime
    )
        : id(id), description(description), status(status), createdTime(createdTime), updatedTime(updatedTime) {
        tasks.insert({id, *this});
        std::cout << "Task Load successfully (ID: " << id << ")" << std::endl;
    }

    bool operator==(const Task &task) const {
        return id == task.id;
    }

    friend std::ostream &operator<<(std::ostream &os, const Task &task) {
        os << "{\n\tID: " << task.id
                << ",\n\tDescription: " << task.description
                << ",\n\tStatus: " << task.status
                << ",\n\tCreated Time: " << task.createdTime
                << ",\n\tUpdated Time: " << task.updatedTime << "\n}";
        return os;
    }

    [[nodiscard]]
    size_t hash() const {
        return std::hash<int>()(id);
    }



private:
    void updateTime() {
        const std::time_t time = std::time(nullptr);
        char updateTimeStr[80] = {0};
        std::strftime(updateTimeStr, 80, "%Y-%m-%d/%H:%M:%S", std::localtime(&time));
        updateTimeStr[std::strlen(updateTimeStr)] = '\0';
        updatedTime = updateTimeStr;
    }

    int id;
    std::string description;
    std::string status = "todo";
    std::string createdTime;
    std::string updatedTime;
};


#endif //TASK_H
