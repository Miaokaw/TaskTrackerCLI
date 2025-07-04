//
// Created by msuperhero on 2025/7/3.
//
#include "task.h"
#include <fstream>
#include <iterator>


void Task::readTasksFromJson(const std::string& jsonFilePath)
{
    std::ifstream file(jsonFilePath);
    std::string line;
    while (std::getline(file, line))
    {
    }
}


void Task::writeTasksToJson(const std::string& jsonFilePath, Task newTask)
{
    std::ifstream fileIn(jsonFilePath);
    std::string content((std::istream_iterator<char>(fileIn)), std::istream_iterator<char>());
    fileIn.close();
    size_t startPos = content.find_last_of('[') + 1;
    size_t endPos = content.find(']', startPos);
    char* createdTime = std::ctime(&newTask.createdTime);
    char* updatedTime = std::ctime(&newTask.updatedTime);
    createdTime[endPos - 1] = '\0';
    updatedTime[endPos - 1] = '\0';
    std::string task = "\n    {\n"
        "        \"id\": " + std::to_string(newTask.id) + ",\n"
        "        \"description\": \"" + newTask.description + "\",\n"
        "        \"status\": \"" + newTask.status + "\",\n"
        "        \"createdTime\": \"" + createdTime + "\",\n"
        "        \"updatedTime\": \"" + updatedTime + "\"\n"
        "    }\n";
    if (startPos != std::string::npos && endPos != std::string::npos)
    {
        content.insert(endPos, "," + task);
    }
    else
    {
        content = "[" + task + "]";
    }
    std::ofstream fileOut(jsonFilePath);
    fileOut << content;
    fileOut.close();
}
