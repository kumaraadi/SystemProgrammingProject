#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client
{
    char client_ip[100];
    int client_pid;
    int msgsock;
};

typedef struct Processe
{
    char process_name[50];
    int pid;
    char * start_time;
    char * end_time;
    char * total_time;
};

