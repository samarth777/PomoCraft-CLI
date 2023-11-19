# PomoCraft: CLI Pomodoro Timer with Task Management

## Overview

PomoCraft is a command-line program that combines the Pomodoro Timer and Task Scheduling functions. It implements the Pomodoro technique, helping users stay focused during work sessions with short breaks. The program allows users to add tasks, mark tasks as completed, and schedule Pomodoro sessions. It uses linked lists, stacks, and queues to manage tasks and sessions efficiently.

## Features

- **Task Management:**
  - Add new tasks.
  - Update completed task list.

- **Pomodoro Functions:**
  - Push and pop tasks onto and from the stack.
  - Enqueue and dequeue tasks into and from the Pomodoro session queue.

- **Display Functions:**
  - Display tasks.
  - Display completed tasks.
  - Display scheduled Pomodoro sessions.

- **Timer Functions:**
  - Start and display the timer for Pomodoro sessions.

## Getting Started

### Prerequisites

- Ensure you have a C compiler installed (e.g., GCC).

### Build

1. Clone the repository:
   ```bash
   git clone https://github.com/samarth777/PomoCraft-CLI.git

3. Compile the program:

   ```bash
   gcc main.c -o PomoCraft

### Run

1. Execute the compiled program:
  ```bash
   ./PomoCraft
```

2. Follow the on-screen prompts to manage tasks and schedule Pomodoro sessions.

3. Enter the number of Pomodoro sessions to be scheduled.

4. Focus during Pomodoro sessions and take breaks accordingly.

5. Continue managing tasks as needed.

## Usage

- Adding a Task:
  - Choose option 1 and enter the task description when prompted.

- Completing a Task:
  - Choose option 2, and follow the prompts to mark a task as completed.

- Scheduling Pomodoro Sessions:
  - Enter the number of Pomodoro sessions to be scheduled when prompted.

## Example


```bash
./PomoCraft
```

Enter your choice
1. Add new task
2. Update completed task list
0. No changes to be made

Enter your choice: 1
Enter task description: Complete README

Enter your choice: 2
Enter task description: Complete README

Scheduled Pomodoro Sessions:
- Complete README
- Implement Feature X
