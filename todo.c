#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    // char* task vs. char task:
    // would only allocate space for a single char instead of a full string (using char task[100] is limiting)
    // typically used for strings in C because they are arrays of characters and an array is basically a pointer to its first element
    char* task;
    int completed; // 1 = true, 0 = false
} Task;

// holds all the different tasks together
// it is set to NULL as default so no memory will be allocated yet
// Task* tasks vs. Task tasks:
// can dynamically allocate memory for this pointer useful when you don't know ahead of time how many tasks you'll need to store
// Task tasks would declare a single Task struct, not an array of tasks

// mainly using these as pointers because we can dynamically allocate memory when we don't know how much we will need later
Task* tasks = NULL;
int length = 0;

// refers to the input string task you need to add in the TODO list
// is a pointer to a character because don't know how long it will be
// is a const so that the data pointed to by the string cannot be modified within the function
void addTask(const char* task)
{
    // dynamically resize the tasks array to hold one more Task struct
    // casting to (Task *) lets the compiler know the memory is an array of Task struct
    tasks = (Task *)realloc(tasks, (length + 1) * sizeof(Task));
    // allocating memory for storing the new task string
    // tasks[length].task accesses the task field inside the new Task struct
    // malloc(strlen(task) + 1) allocates memory to hold the string task, the +1 is to accomodate for the null terminator
    // the result is cast to (char *) since malloc returns a void*
    tasks[length].task = (char *)malloc(strlen(task) + 1);
    // initializes the completed field of the new task
    // sets the completed status of the new task to 0, indicating that the task is not yet completed
    tasks[length].completed = 0;

    // copies the task string into the allocated memory
    // copies the string passed as the task parameter into the memory that was allocated for tasks[length].task
    strcpy(tasks[length].task, task); // strcpy(into, from)
    // updates the length of the tasks array
    length++;
    printf("Task added");
}

void listTasks() 
{

}

void deleteTask() 
{

}

void markCompleted() 
{

}

void editTask() 
{

}

int main()
{
    printf("Hello Todo!\n");

    return 0;
}