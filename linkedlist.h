#include <stdio.h>
#include <time.h>

typedef struct Clients
{
    char client_ip[100];
    int client_pid;
    int msgsock;
    struct Clients *next;
} Clients;

typedef struct Processes
{
    char process_name[50];
    int pid;
    struct tm start_time;
    struct tm end_time;
    struct tm total_time;
    struct Processes *next;
} Processes;
// void add_client(char str[], int msgsock, Clients *head)
// {
//     if (head == NULL)
//     {
//         strcpy(head->client_ip, str);
//         head->msgsock = msgsock;
//         head->next = NULL;
//     }
//     else
//     {
//         Clients *newClient = NULL;
//         newClient = malloc(sizeof(Clients));
//         // newClient->client_ip = str;
//         strcpy(newClient->client_ip, str);
//         newClient->msgsock = msgsock;
//         newClient->next = head;
//         head->next = newClient;
//     }
// }

// void delete_client(char str[], Clients *head)
// {
//     Clients *current = NULL;
//     current = malloc(sizeof(Clients));

//     while (current != NULL && !strcmp(current->client_ip, str) == 0)
//     {
//         current = current->next;
//     }
//     if (current == NULL)
//     {
//         //Client Not FOund
//     }
//     else
//     {
//     }
// }

// void show_clients(Clients *head)
// {
// }

void add_Process(char process_name[], int pid, struct tm start_time, Processes *head)
{
    if (head == NULL)
    {
        strcpy(head->process_name, process_name);
        head->pid = pid;
        head->start_time = start_time;
        head->next = NULL;
    }
    else
    {
        Processes *newProcess = NULL;
        newProcess = malloc(sizeof(Processes));

        strcpy(newProcess->process_name, process_name);
        newProcess->pid = pid;
        newProcess->start_time = start_time;
        newProcess->next = head;
        head->next = newProcess;
    }
}
void remove_process(Processes *head, int pid, time_t end_time)
{
}
void showProcesses(Processes *head, int msgsock)
{
    Processes *current = head;
    char detail[1024];
    char str[50];

    while (current != NULL)
    {
        strcat(detail, "Process Name: ");
        sprintf(str, "%d", current->pid);
        strcat(detail, current->process_name);
        strcat(detail, "\n");
        strcat(detail, "Process ID: ");
        strcat(detail, str);
        strcat(detail, "\n");
        strcat(detail, "Start Time: ");
        // strcat(detail, current->start_time);
        // strcat(detail, "\n");

    }
    strcat(detail, "\n\n\n");
    write(msgsock, detail, strlen(detail));
}