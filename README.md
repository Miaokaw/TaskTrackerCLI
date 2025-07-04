# Task Tracker CLI by C++

A solution for the [Task Tracker](https://roadmap.sh/projects/task-tracker)

## How to run

```bash
# clone the repository
git clone git@github.com:Miaokaw/TaskTrackerCLI.git
cd TaskTrackerCLI
```

Run the following command to build the project:

```bash
# Make sure you have CMake and a C++ compiler installed
mkdir build && cd build
cmake ..
make
```
And then you can run the program.

Example commands:
```bash
# Show help
./tt help 
# Add a new task
./tt add "Task 0"
Output: Task added successfully (ID: 1)
# List all tasks
./tt list 
# Mark task 1 as in progress
./tt mark-in-progress 0 
# display task 0
./tt delete 0
```