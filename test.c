#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// typedef struct Client
// {
//     char *client_ip;
//     int msgsock;
//     char *start_time;
//     char *end_time;
//     char *status;
//     struct Client *next;
// };

// typedef struct Process
// {
//     char *process_name;
//     int pid;
//     char *start_time;
//     char *end_time;
//     char *status;
//     struct Process *next;
// };
// void printlist(struct Process *p, int count);
// char *gettime()
// {
//     time_t now = time(0);
//     struct tm *ltm = localtime(&now);
//     char *time;
//     sprintf(time, "%d:%d:%d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
//     return time;
// }
int main()
{
    char str[50] = "";
    strcat(str, "\033[1;31m");
    strcat(str, "Connected");  //RED
     strcat(str, "\033[0m\n");
    
    

    write(STDOUT_FILENO, str, strlen(str));
    printf("%d", strlen(str));
}