//
// Created by msuperhero on 2025/7/3.
//
#include "task.h"

#include <cstring>
#include <fstream>
#include <iterator>
#include <ranges>


void Task::readFromJson(const std::string &jsonFilePath) {
    std::ifstream fileIn(jsonFilePath);
    std::string content((std::istream_iterator<char>(fileIn)), std::istream_iterator<char>());
    fileIn.close();
    size_t startPos = content.find_last_of('[') + 1;
    size_t endPos = content.find(']', startPos);
    if (startPos != std::string::npos && endPos != std::string::npos) {
        size_t pos = startPos;
        while (pos < endPos) {
            size_t idPos = content.find("\"id\":", pos);
            if (idPos == std::string::npos || idPos >= endPos) break;
            idPos += 5; // Move past "id":
            size_t idEnd = content.find(',', idPos);
            int id = std::stoi(content.substr(idPos, idEnd - idPos));

            size_t descPos = content.find("\"description\":", idEnd);
            if (descPos == std::string::npos || descPos >= endPos) break;
            descPos += 15; // Move past "description":
            size_t descEnd = content.find('"', descPos + 1);
            std::string description = content.substr(descPos, descEnd - descPos);

            size_t statusPos = content.find("\"status\":", descEnd);
            if (statusPos == std::string::npos || statusPos >= endPos) break;
            statusPos += 10; // Move past "status":
            size_t statusEnd = content.find('"', statusPos + 1);
            std::string status = content.substr(statusPos, statusEnd - statusPos);

            size_t createdTimePos = content.find("\"createdTime\":", statusEnd);
            if (createdTimePos == std::string::npos || createdTimePos >= endPos) break;
            createdTimePos += 15; // Move past "createdTime":
            size_t createdTimeEnd = content.find('"', createdTimePos + 1);
            std::string createdTime = content.substr(createdTimePos, createdTimeEnd - createdTimePos);

            size_t updatedTimePos = content.find("\"updatedTime\":", createdTimeEnd);
            if (updatedTimePos == std::string::npos || updatedTimePos >= endPos) break;
            updatedTimePos += 15; // Move past "updatedTime":
            size_t updatedTimeEnd = content.find('"', updatedTimePos + 1);
            std::string updatedTime = content.substr(updatedTimePos, updatedTimeEnd - updatedTimePos);

            auto task = new Task(id, description, status, createdTime, updatedTime);
            pos = content.find('{', updatedTimeEnd);
        }
    }
}


void Task::writeToJson(const std::string &jsonFilePath, const Task &newTask) {
    std::ifstream fileIn(jsonFilePath);
    std::string content((std::istream_iterator<char>(fileIn)), std::istream_iterator<char>());
    fileIn.close();
    size_t startPos = content.find_last_of('[') + 1;
    size_t endPos = content.find(']', startPos);
    std::string task = "\n    {\n"
                       "        \"id\": " + std::to_string(newTask.id) + ",\n"
                       "        \"description\": \"" + newTask.description + "\",\n"
                       "        \"status\": \"" + newTask.status + "\",\n"
                       "        \"createdTime\": \"" + newTask.createdTime + "\",\n"
                       "        \"updatedTime\": \"" + newTask.updatedTime + "\"\n"
                       "    }\n";
    if (startPos != std::string::npos && endPos != std::string::npos) {
        content.insert(endPos, "," + task);
    } else {
        content = "[" + task + "]";
    }
    std::ofstream fileOut(jsonFilePath);
    fileOut << content;
    fileOut.close();
}

void Task::del(const int id) {
    if (const auto it = tasks.find(id); it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task deleted successfully (ID: " << id << ")" << std::endl;
    } else {
        std::cerr << "Task not found (ID: " << id << ")" << std::endl;
    }
    std::ofstream fileOut("./tasks.json");
    fileOut << "";
    fileOut.close();
    for (const auto &task: tasks | std::views::values) {
        writeToJson("./tasks.json", task);
    }
}

void Task::update(int id, std::string_view newDescription) {
    if (const auto it = tasks.find(id); it != tasks.end()) {
        Task &selectedTask = it->second;
        selectedTask.description = newDescription;
        selectedTask.updateTime();
        std::ofstream fileOut("./tasks.json");
        fileOut << "";
        fileOut.close();
        for (const auto &task: tasks | std::views::values) {
            writeToJson("./tasks.json", task);
        }
        std::cout << "Task updated successfully (ID: " << id << ")" << std::endl;
    } else {
        std::cerr << "Task not found (ID: " << id << ")" << std::endl;
    }
}

void Task::mark(const int id, const std::string_view newStatus) {
    if (const auto it = tasks.find(id); it != tasks.end()) {
        Task &selectedTask = it->second;
        selectedTask.status = newStatus;
        selectedTask.updateTime();
        std::ofstream fileOut("./tasks.json");
        fileOut << "";
        fileOut.close();
        for (const auto &task: tasks | std::views::values) {
            writeToJson("./tasks.json", task);
        }
        std::cout << "Task status updated successfully (ID: " << id << ")" << std::endl;
    } else {
        std::cerr << "Task not found (ID: " << id << ")" << std::endl;
    }
}



void Task::list() {
    std::cout << "Tasks List:\n";
    for (const auto &task: tasks | std::views::values) {
        std::cout << task;
        std::cout << "," << std::endl;
    }
}

void Task::list(const char *str) {
    std::cout << str <<"Tasks List:\n";
    for (const auto &task: tasks | std::views::values) {
        if (task.status == str) {
            std::cout << task;
            std::cout << "," << std::endl;
        }
    }
}

