#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 100        // Defining Max_Desc as 100
#define FILENAME "task.dat" // Defining Filename as "task.dat" for binary storing

// Sructure of Task Manager
typedef struct Task
{
    int id;
    char description[MAX_DESC];
    int priority;
    char DueDate[11]; // YYYY-DD-MM
    int completion;
    struct Task *next; // Pointer to next task
} Tasks;

// Features Prototypes
void addTask(Tasks **head, int *id);
void viewTask(Tasks *head);
void delTask(Tasks **head, int id);
void markTaskCompleted(Tasks *head, int id);
void SaveTask(Tasks *head);
void cleartasks(Tasks **head);
void LoadTask(Tasks **head, int *task_id);

// Main
int main()
{

    Tasks *task_list = NULL;
    int task_id = 1, choice;

    // User Interface

    printf("==== TASK MANAGER ====\n");
    printf("Welcome! Manage your tasks easily with this Task Manager.\n");

    while (1)
    {
        printf("|...MENU...|\n");
        printf("---------------------------\n");
        printf("1.Add Task\n");
        printf("---------------------------\n");
        printf("2.View Tasks\n");
        printf("---------------------------\n");
        printf("3.Delete Task\n");
        printf("---------------------------\n");
        printf("4.Mark Task if Completed\n");
        printf("---------------------------\n");
        printf("5.Save Task\n");
        printf("---------------------------\n");
        printf("6.Load Tasks\n");
        printf("---------------------------\n");
        printf("7.Exit\n");
        printf("---------------------------\n");
        printf("Enter Your Command:");
        scanf("%d", &choice);

        // User Choices
        switch (choice)
        {
        case 1:
            printf("Add the task\n");
            addTask(&task_list, &task_id);
            break;

        case 2:
            printf("\n");
            viewTask(task_list);
            break;

        case 3:
        {
            int id;
            printf("Enter task id to be deleted:\n");
            scanf("%d", &id);
            delTask(&task_list, id);
            break;
        }
        case 4:
        {
            int id;
            printf("Enter task id to be marked completed:\n");
            scanf("%d", &id);
            markTaskCompleted(task_list, id);
            break;
        }
        case 5:
            printf("Saving task.....\n");
            printf("\n");
            SaveTask(task_list);
            break;

        case 6:
            printf("Loading tasks...\n");
            printf("\n");
            LoadTask(&task_list, &task_id);
            viewTask(task_list);
            break;

        case 7:
            printf("Exiting....\n");
            printf("\n");
            exit(0);

        default:
            printf("Invalid Choice\n Try again.\n");
            break;
        }
    }
    return 0;
}

// static int last_id = 0;

//  Function to add a new task
void addTask(Tasks **head, int *id)
{
    // Creating a new task
    Tasks *newTask = (Tasks *)malloc(sizeof(Tasks));
    // CHeck if a task is created or not
    if (newTask == NULL)
    {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    // Increasing id to store the task
    newTask->id = (*id)++;

    printf("Enter Task Description\n");

    getchar(); // getchar() to Consume the Newline Left by scanf: When scanf is used before fgets, it typically leaves a newline character (\n) in the input buffer. This newline is read by fgets as the end of input, which causes fgets to stop reading without waiting for actual user input. Using getchar() after scanf consumes this leftover newline, so the input buffer is clear for fgets.

    fgets(newTask->description, MAX_DESC, stdin);

    // Here, fgets reads the entire line of input up to MAX_DESC - 1 characters or until a newline (\n) is encountered. This is helpful because fgets can handle spaces in input, unlike scanf.

    newTask->description[strcspn(newTask->description, "\n")] = '\0';

    // The function strcspn is part of the C standard library and is used to find the first occurrence of any character from a specified set in a string.

    //     strcspn(new_task->description, "\n") finds the index of the newline character \n in      new_task->description.

    //  If a newline character is found, strcspn returns its position in the string, and description    [position] = '\0'; replaces it with the null terminator \0. This effectively removes the newline from the end of the input.

    //  If no newline character is found (e.g., if the string was already trimmed or filled to maximum length), it does nothing, so description remains unchanged.

    // to check if the priority enetered is between 1 to 5
    while (1)
    {
        printf("Enter Priority of Task(1-5):\n");
        scanf("%d", &newTask->priority);
        if (newTask->priority >= 1 && newTask->priority <= 5)
        {
            break; // break if priority is bw 1-5
        }
        else
        {
            printf("Invalid Priority!! Please enter the priority between 1-5.\n");
        }
    }

    while (1)
    {
        printf("Enter Due Date (YYYY-DD-MM):\n");
        scanf(" %10s", newTask->DueDate);
        if (strlen(newTask->DueDate) == 10)
        {
            break;
        }
        else
        {
            printf("The Format of Date enetered is wrong. Please enter a correct format.\n");
        }
    }

    newTask->completion = 0;

    // New LL will be created and added
    newTask->next = *head;
    *head = newTask;
    printf("\n");
    printf("Task Added : %d -\t%s\n", newTask->id, newTask->description);
    printf("\n");
}

// Function to view Task
void viewTask(Tasks *head)
{
    // Condition if there is no tasks
    if (head == NULL)
    {
        printf("Nothing to Show\n");
        printf("\n");
        return;
    }
    printf(".....Tasks List.....\n");
    while (head != NULL)
    {
        printf("ID : %d\n", head->id);
        printf("....................\n");
        printf("DESCRIPTION : %s\n", head->description);
        printf("....................\n");
        printf("Priority : %d\n", head->priority);
        printf("....................\n");
        printf("Due Date : %s\n", head->DueDate);
        printf("....................\n");
        printf("Status : %s\n", (head->completion == 1) ? "Completed" : "Pending");
        printf("....................\n");
        printf("\n");
        head = head->next;
    }
}

// Function to Delete a task from id
void delTask(Tasks **head, int id)
{
    // Check if list is empty
    if (*head == NULL)
    {
        printf("Nothing to delete.\n");
        printf("\n");
        return;
    }
    // Making 2 pointers for traversing
    Tasks *temp = *head, *prev = NULL;

    // Condition if the task to delete is same as 'head'
    if (temp != NULL && temp->id == id)
    {
        *head = (*head)->next;
        free(temp);
        temp = NULL;
        printf("Task with id %d has been Deleted\n", id);
        printf("\n");
        SaveTask(*head);
        return;
    }

    // Traversing both temp and prev till its NULL or id found
    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    // return nothing if,  id not found
    if (temp == NULL)
    {
        printf("Task with id %d not Found\n", id);
        printf("\n");
        return;
    }

    // Connecting prev to temp next and removing temp
    prev->next = temp->next;
    free(temp);
    printf("Task with id %d has been Deleted Successfully\n", id);
    printf("\n");
    // Saving new LL after removing task
    SaveTask(*head);
}

// Function to Mark task complete by id
void markTaskCompleted(Tasks *head, int id)
{

    Tasks *temp = head;
    // traversing temp to find id enetered by user
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            // if already completed return this
            if (temp->completion == 1)
            {
                printf("Task has already been marked completed!!\n");
                printf("\n");
                return;
            }
            // else mark it complete
            printf("%s has been Completed\n", temp->description);
            printf("\n");
            printf("\n");
            temp->completion = 1;
            return;
        }
        temp = temp->next;
    }
    // task not found after traversing till null
    printf("Task not found\n");
    printf("\n");
}

// Function to Save tasks
void SaveTask(Tasks *head)
{
    // Opening file in write binary mode
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL)
    {
        printf("Failed to open file for saving\n");
        printf("\n");
        return;
    }

    Tasks *current = head;
    while (current != NULL)
    {
        // writing task in wb mode of size same as the tasks structure
        fwrite(current, sizeof(Tasks), 1, file);
        current = current->next;
    }

    fclose(file);
}

// Function to Load all tasks
void LoadTask(Tasks **head, int *task_id)
{
    Tasks **current = head;
    // Clearing old tasks first
    cleartasks(current);
    // opening file in read binary mode
    FILE *file = fopen(FILENAME, "rb");

    // check if its opened or not
    if (file == NULL)
    {
        printf("Failed to open file for loading\n");
        printf("\n");
        return;
    }

    int loaded = 0; // to check if its loaded or not
    while (1)
    {

        Tasks *newtasks = (Tasks *)malloc(sizeof(Tasks));
        if (newtasks == NULL)
        {
            printf("Memory Allocation Failed\n");
            printf("\n");
            fclose(file);
            return;
        }

        // reading tasks
        size_t byteRead = fread(newtasks, sizeof(Tasks), 1, file);
        // size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

        if (byteRead != 1)
        {
            free(newtasks);
            break;
        }

        if (newtasks->id >= *task_id)
        {
            *task_id = newtasks->id + 1;
        }

        // Loading Task in a LL form
        newtasks->next = *head;
        *head = newtasks;
        loaded = 1;
    }
    fclose(file);

    // if loaded successfullly
    if (loaded)
    {
        printf("Tasks Have been loaded successfully.\n");
        printf("\n");
    }
    else
    {
        printf("No task found to load\n");
        printf("\n");
    }
}

// Clearing Tasks for Loading it later (a supportive Function)
void cleartasks(Tasks **head)
{
    Tasks *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
