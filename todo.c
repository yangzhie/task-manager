#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    // char* task vs. char task:
    // would only allocate space for a single char instead of a full string (using char task[100] is limiting)
    // typically used for strings in C because they are arrays of characters and an array is basically a pointer to its first element
    char *task;
    int completed; // 1 = true, 0 = false
} Task;

// holds all the different tasks together
// it is set to NULL as default so no memory will be allocated yet
// Task* tasks vs. Task tasks:
// can dynamically allocate memory for this pointer useful when you don't know ahead of time how many tasks you'll need to store
// Task tasks would declare a single Task struct, not an array of tasks

// mainly using these as pointers because we can dynamically allocate memory when we don't know how much we will need later
Task *tasks = NULL;
int length = 0;

// refers to the input string task you need to add in the TODO list
// is a pointer to a character because don't know how long it will be
// is a const so that the data pointed to by the string cannot be modified within the function
void addTask(const char *task)
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
    printf("Task added.\n");
}

// no arguments required
void listTasks()
{
    const char *status;

    for (int i = 0; i < length; i++)
    {
        if (tasks[i].completed == 1)
        {
            status = "done.\n";
        }
        else
        {
            status = "not done.\n";
        }

        printf("%d. %s is %s\n", i, tasks[i].task, status);
    }
}

void markCompleted(int index)
{
    if (index <= length && index > 0)
    {
        tasks[index - 1].completed = 1;
        printf("Task is now completed.\n");
    }
    else
    {
        printf("Invalid index.\n");
    }
}

void deleteTask(int index)
{
    if (index <= length && index > 0)
    {
        index--;
        free(tasks[index].task);

        for (int i = index; i < length - 1; i++)
        {
            tasks[i] = tasks[i + 1];
        }

        length--;
        tasks = (Task *)realloc(tasks, (length * sizeof(Task)));
    }
    else
    {
        printf("Invalid index.\n");
    }
}

void editTask(int index, const char *task)
{
    if (index <= length && index > 0)
    {
        index--;

        char *editedTask = (char *)realloc(tasks[index].task, strlen(task) + 1);

        if (editedTask != NULL)
        {
            tasks[index].task = editedTask;
            strcpy(tasks[index].task, task);
            printf("Task updated successfully.\n");
        }
        else
        {
            printf("Memory allocation failed.\n");
        }
    }
    else
    {
        printf("Invalid index.\n");
    }
}

int main()
{
    printf("\nOptions\n");
    printf("1. Add task\n");
    printf("2. List all tasks\n");
    printf("3. Mark a task as completed\n");
    printf("4. Edit task\n");
    printf("5. Delete task\n");
    printf("6. Exit\n");

    int userInput;
    int programIsRunning = 1;
    char taskInput[100];
    int indexInput;

    while (programIsRunning)
    {
        printf("Please enter a task to perform: ");
        scanf("%d", &userInput);

        switch (userInput)
        {
        case 1:
            printf("Enter task: ");
            // gets rid of a new line if there is one from scanf
            getchar();
            // used to read a line of text until a new line from the standard input (stdin)
            // taskInput is an array of characters that the fgets method reads
            // sizeof ensures the fgets doesn't read more than it is supposed to
            fgets(taskInput, sizeof(taskInput), stdin);
            // this removes the newline char from the userinput
            // strcpsn finds the position of the newline char and replaces it with a null terminator
            taskInput[strcspn(taskInput, "\n")] = '\0';
            addTask(taskInput);

            break;
        case 2:
            listTasks();

            break;
        case 3:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            markCompleted(indexInput);

            break;
        case 4:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            printf("Enter edited task: ");
            getchar();
            fgets(taskInput, sizeof(taskInput), stdin);
            taskInput[strcspn(taskInput, "\n")] = '\0';

            editTask(indexInput, taskInput);

            break;
        case 5:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            deleteTask(indexInput);

            break;
        case 6:
            programIsRunning = 0;

            break;
        default:
            printf("Invalid choice.");
        }
    }

    free(tasks);

    return 0;
}