#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h> 



typedef struct Process
{
    char process_name[50];
    int pid;
    char start_time[20];
    char end_time[20];
    char status[10];
}var2;
typedef struct Client
{
    char client_ip[50];
    int msgsock;
    char start_time[20];
    char end_time[20];
    char status[10];
    struct Process *pro_list;
    int count;
}var1;



// char *gettime()
// {
//     time_t now = time(0);
//     struct tm *ltm = localtime(&now);
//     char *time;
//     sprintf(time, "%d:%d:%d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
//     return time;
// }
int validate(char *arr[], int n)
{

    int i = 0;
    for (i = 1; i < n; i++)
    {
        char c = (char)*arr[i];
        if (!isdigit(c))
        {
            return 0;
        }
    }
    return 1;
}

float add(char *arr[], int n)
{
    int i;
    float sum = 0;

    for (i = 1; i < n; i++)
    {
        int len = strlen(arr[i]) + 1;
        char str[len];
        strcpy(str, arr[i]);
        str[len] = '\0';
        float num = atof(str);
        sum = sum + num;
    }
    return sum;
}

int Handle_Add(int tokens, char *TokensArray[], int msgsock)
{
    char char_result[20];
    if (tokens > 1)
    {
        if (validate(TokensArray, tokens) == 1)
        {
            int s = sprintf(char_result, "%f\n\n", add(TokensArray, tokens));
            write(msgsock, char_result, s);
        }
        else
        {
            write(msgsock, "non-numeric can't be added!\n", 28);
        }
    }
    else
    {
        write(msgsock, "No number to add! Try again.\n", 29);
    }
}
//Client
// void add_Client(struct Client list[0], int count, int msgsock, char ip[])
// {
//     write(STDOUT_FILENO, ip, strlen(ip));
//     list[count].client_ip = ip;
//     list[count].msgsock = msgsock;
//     // list[count].start_time = gettime();
//     list[count].status = "Active";
//     list[count].end_time = "-";
// }
// void show_Clients(struct Client list[0], int count)
// {
//     char str[20];
//     int i = 0;
//     for (i = 0; i < count; i++)
//     {
//         write(STDOUT_FILENO, list[i].client_ip, strlen(list[i].client_ip));
//         write(STDOUT_FILENO, "\n", 1);
//         sprintf(str, "%d", list[i].msgsock);
//         write(STDOUT_FILENO, str, strlen(str));
//         write(STDOUT_FILENO, "\n", 1);
//         write(STDOUT_FILENO, list[i].status, strlen(list[i].status));
//         write(STDOUT_FILENO, "\n", 1);
//         write(STDOUT_FILENO, list[i].start_time, strlen(list[i].start_time));
//         write(STDOUT_FILENO, "\n", 1);
//         write(STDOUT_FILENO, list[i].end_time, strlen(list[i].end_time));
//         write(STDOUT_FILENO, "---", 3);
//     }
// }

//Processes

// void add_Process(struct Process list[0], int count, char *arr[], int pid, char *start_time)
// {

//     list[count].process_name = arr[1];
//     list[count].pid = pid;
//     list[count].start_time = start_time;
//     list[count].status = "Active";
//     list[count].end_time = "-";
// }
// void showProcesses(struct Process list[0], int count, int msgsock)
// {
//     int i;
//     char *process_info;
//     char str[20];
//     process_info = "Processes:\n";
//     for (i = 0; i < count; i++)
//     {
//         write(STDOUT_FILENO, list[i].process_name, strlen(list[i].process_name));
//         // strcat(process_info, list[i].process_name);
//         write(msgsock, list[i].process_name, strlen(list[i].process_name));
//         write(msgsock, "\n", 1);
//         // strcat(process_info, "\n");
//         sprintf(str, "%d", list[i].pid);
//         // strcat(process_info, str);
//         write(msgsock, str, strlen(str));
//         write(msgsock, "\n", 1);
//         // strcat(process_info, "\n");
//         // strcat(process_info, list[i].status);
//         write(msgsock, list[i].status, strlen(list[i].status));
//         write(msgsock, "\n", 1);
//         // strcat(process_info, "\n");
//         // strcat(process_info, list[i].start_time);
//         write(msgsock, list[i].start_time, strlen(list[i].start_time));
//         write(msgsock, "\n", 1);
//         // strcat(process_info, "\n");
//         // strcat(process_info, list[i].end_time);
//         write(msgsock, list[i].end_time, strlen(list[i].end_time));
//         write(msgsock, "\n", 1);
//         // strcat(process_info, "\n-----");
//         // strcat(process_info, "\n");
//     }
//     // write(msgsock, process_info, strlen(process_info));
// }

// int Handle_run(char *arr[], struct Process list[0], int count, int msgsock)
// {
    
   
// }
int Client_Found(struct Client list[0], int count){
    int i = 0;
    int ret = 1;
    for( i = 0; i < count; i++)
    {
        
    }
    
}
