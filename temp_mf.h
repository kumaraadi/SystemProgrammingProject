#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <wait.h>
#include <string.h>
#include "temp_ll.h"


char char_result[20];

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

int Handle_run(char *arr[], Processes *head)
{
    int len = strlen(arr[1]) + 1;
    char str[len];
    strcpy(str, arr[1]);
    // str[len] = '\0';
    int status;
    write(STDOUT_FILENO, "run\n", 4);
    int pid = fork();

    if (pid == 0)
    {
        char hello[20];
        int var = sprintf(hello, "%i", getpid());
        time_t mytime = time(NULL);
        struct tm current_time = *localtime(&mytime);


        add_Process(arr[1], var, current_time, head);
        write(STDOUT_FILENO, hello, var);
        execlp(arr[1], arr[1], NULL);
    }
    return 0;
}
