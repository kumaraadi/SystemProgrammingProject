#include <stdio.h>
#include <time.h>

typedef struct Client
{
    char client_ip[100];
    int msgsock;
    char *start_time;
    char *end_time;
    char *status;
    struct Client *next;
} Clients;

typedef struct Process
{
    char process_name[50];
    int pid;
    char *start_time;
    char *end_time;
    char *status;
    struct Process *next;
} Processes;

// void add_Process(char process_name[], int pid, char *start_time, Processes *head)
// {
//     Processes *newProcess = NULL;
//     newProcess = malloc(sizeof(Processes));

//     strcpy(newProcess->process_name, process_name);
//     newProcess->pid = pid;
//     newProcess->start_time = start_time;
//     // newProcess->next = NULL;

//     if (head == NULL)
//     {
//         head = newProcess;
//         head->next = NULL;
//     }
//     else
//     {
//         // Processes *temp = head;
//         // while (temp->next != NULL)
//         // {
//         //     temp = temp->next;
//         // }
//         // temp->next = newProcess;
//         // temp->next->next = NULL;
//         newProcess->next = head;
//         head = newProcess;
//     }
// }
// void remove_process(Processes *head, int pid, time_t end_time)
// {
// }
// void showProcesses(Processes *head, int msgsock)
// {

//     char detail[1024] = "LIST:\n";
//     Processes *current = head;
//     char str[50];

//     while (current != NULL)
//     {

//     //     write(msgsock, "here\n", 5);

//     // write(msgsock, current->process_name, strlen(current->process_name));
//     //     strcat(detail, "Process Name: ");
//     //     strcat(detail, current->process_name);
//     //     strcat(detail, "\n");

//     //     sprintf(str, "%d", current->pid);
//     //     strcat(detail, "Process ID: ");
//     //     strcat(detail, str);
//     //     strcat(detail, "\n");

//     //     strcat(detail, "Start Time: ");
//     //     strcat(detail, current->start_time);
//     //     strcat(detail, "\n");

//     //     strcat(detail, "End Time: ");
//     //     strcat(detail, current->end_time);

//     //     strcat(detail, "\n");
//     //     strcat(detail, "\n");
//         current = current->next;
//     }

//     write(msgsock, detail, strlen(detail));
// }
// void add_client(char str[], int msgsock, Clients *head, char * start_time)
// {
//     Clients *newClient = NULL;
//     newClient = malloc(sizeof(Clients));

//     // strcpy(newClient->client_ip, str);
//     // strcpy(newClient->start_time, start_time);
//     // strcpy(newClient->status, "Active");
//     // strcpy(newClient->end_time, "-");


//     if (head == NULL)
//     {
//         write(STDOUT_FILENO, "1\n", 2);
//         head = newClient;
//         head->next = NULL;
//     }
//     else
//     {

//         write(STDOUT_FILENO, "2\n", 2);
//         newClient->next = head;
//         head = newClient;
//     }
// }


// void show_clients(Clients *head)
// {
//     Clients *current = head;

//     while(current != NULL){
//         write(STDOUT_FILENO, current->status, strlen(current->status));
//         current = current->next;
//     }
// }


// // void delete_client(char str[], Clients *head)
// // {
// //     Clients *current = NULL;
// //     current = malloc(sizeof(Clients));

// //     while (current != NULL && !strcmp(current->client_ip, str) == 0)
// //     {
// //         current = current->next;
// //     }
// //     if (current == NULL)
// //     {
// //         //Client Not FOund
// //     }
// //     else
// //     {
// //     }
// // }
