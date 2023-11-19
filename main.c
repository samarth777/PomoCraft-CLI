/**
 * @file main.c
 * @brief Combine the Pomodoro Timer and the Task Scheduling Functions
 * 
 * This file contains the implementation of a program that combines the Pomodoro Timer and the Task Scheduling functions.
 * The program allows users to add tasks, mark tasks as completed, and schedule Pomodoro sessions.
 * It uses linked lists, stacks, and queues to manage tasks and sessions.
 * The Pomodoro Timer helps users focus on a task for a specific duration, followed by a short break.
 * The program prompts users to enter the number of Pomodoro sessions to be scheduled and manages the sessions accordingly.
 * 
 * The program is divided into the following sections:
 * - Task management: Functions to create, add, and remove tasks from the task list.
 * - Pomodoro functions: Functions to push and pop tasks from the stack, and enqueue and dequeue tasks from the queue.
 * - Display functions: Functions to display tasks, completed tasks, and scheduled Pomodoro sessions.
 * - Task manager: Function to manage user interactions and perform actions based on user choices.
 * - Timer functions: Functions to start and display the timer for Pomodoro sessions.
 * - Main function: Entry point of the program.
 */

//Combine the Pomodoro Timer and the Task Scheduling Functions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// Task management

//Pomodoro Functions
// Structure for a task
typedef struct Task {
    char description[100];
    struct Task* next;
} Task;

// Structure for a stack node
typedef struct StackNode {
    struct Task* task;
    struct StackNode* next;
} StackNode;

// Structure for a queue node
typedef struct QueueNode {
    struct Task* task;
    struct QueueNode* next;
} QueueNode;

// Structure for Pomodoro timer session
typedef struct PomodoroSession {
    int duration; // in minutes
} PomodoroSession;

Task* taskList = NULL;
StackNode* stackTop = NULL;
QueueNode* sessionQueueFront = NULL;
QueueNode* sessionQueueRear = NULL;

// Function to create a new task
Task* createTask(const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    snprintf(newTask->description, sizeof(newTask->description), "%s", description);
    newTask->next = NULL;

    return newTask;
}

// Function to push a task onto the task list (linked list)
void addTask(Task** head, const char* description) {
    Task* newTask = createTask(description);
    newTask->next = *head;
    *head = newTask;
}


// Function to pop a task from the task list
Task* popTask(Task** head, char* description) {
    if (*head == NULL) {
        return NULL; // Task list is empty
    }

    Task* currentTask = *head;
    Task* previousTask = NULL;

    while (currentTask != NULL) {
        if (strcmp(currentTask->description, description) == 0) {
            if (previousTask == NULL) {
                *head = currentTask->next;
            } else {
                previousTask->next = currentTask->next;
            }
            currentTask->next = NULL;
            return currentTask;
        }
        previousTask = currentTask;
        currentTask = currentTask->next;
    }

    return NULL; // Task with given description not found
}

// Function to push a task onto the stack
void pushToStack(StackNode** top, Task* task) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->task = task;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a task from the stack
Task* popFromStack(StackNode** top) {
    if (*top == NULL) {
        return NULL; // Stack is empty
    }

    StackNode* poppedNode = *top;
    Task* poppedTask = poppedNode->task;
    *top = poppedNode->next;

    free(poppedNode);

    return poppedTask;
}

// Function to enqueue a task (Pomodoro session) into the queue
void enqueue(QueueNode** front, QueueNode** rear, Task* task) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->task = task;
    newNode->next = NULL;

    if (*rear == NULL) {
        // Queue is empty
        *front = *rear = newNode;
    } else {
        // Add the new node to the end of the queue
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

// Function to dequeue a task from the queue
Task* dequeue(QueueNode** front, QueueNode** rear) {
    if (*front == NULL) {
        return NULL; // Queue is empty
    }

    QueueNode* dequeuedNode = *front;
    Task* dequeuedTask = dequeuedNode->task;

    *front = (*front)->next;

    if (*front == NULL) {
        // Queue is now empty
        *rear = NULL;
    }

    free(dequeuedNode);

    return dequeuedTask;
}

// Function to display tasks
void displayTasks(Task* head) {
    printf("Tasks:\n");
    while (head != NULL) {
        printf("- %s\n", head->description);
        head = head->next;
    }
}

// Function to display completed tasks from the stack
void displayCompletedTasks(StackNode* top) {
    printf("Completed Tasks:\n");
    while (top != NULL) {
        printf("- %s\n", top->task->description);
        top = top->next;
    }
}

// Function to display scheduled Pomodoro sessions from the queue
void displayScheduledSessions(QueueNode* front) {
    printf("Scheduled Pomodoro Sessions:\n");
    while (front != NULL) {
        printf("- %s\n", front->task->description);
        front = front->next;
    }
}

void taskManager() {
    while(1)
    {
        int choice;
        char taskDescription[100];
        printf("Enter your choice\n");
        printf("1. Add new task\n");
        printf("2. Update completed task list\n");
        printf("0. No changes to be made\t");

        // Get user choice
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add Task
                printf("Enter task description: ");
                scanf(" %[^\n]", taskDescription);
                addTask(&taskList, taskDescription);
                break;

            case 2:
                // Complete Task

                if (taskList != NULL) {
                    printf("Enter task description: ");
                    scanf(" %[^\n]", taskDescription);
                    Task* completedTask = popTask(&taskList, taskDescription);
                    if (completedTask != NULL) {
                        pushToStack(&stackTop, completedTask);
                    } else {
                        printf("Task with given description not found.\n");
                    }
                } else {
                    printf("No tasks to complete.\n");
                }
                break;

            case 0:
                return;
        }

    }
}



void start_timer(int duration, const char *message) {
    time_t start_time, current_time;
    int elapsed_time = 0;

    time(&start_time);

    printf("%s\n", message);

    while (1) {
        time(&current_time);
        elapsed_time = difftime(current_time, start_time);

        if (elapsed_time >= duration) {
            printf("Time's up!\n");
            break;
        }

        printf("Time remaining: %02d:%02d\r", (duration - elapsed_time) / 60, (duration - elapsed_time) % 60);
        fflush(stdout);
        sleep(1);
    }
}

int main() {
    taskManager();
    int num;
    printf("Enter number of pomodoro sessions to be scheduled: ");
    scanf("%d",&num);
    while (num) {
        start_timer(10, "Pomodoro started. Focus!");
        printf("\nTake a short break.\n");
        start_timer(10, "Short break. Relax!");
        printf("\n");
        taskManager();
        num--;
    }
    printf("\nThank you for using the Pomodoro Timer!\n");
    return 0;
}

