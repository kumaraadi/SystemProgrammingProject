#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
bool validateCommand(char *InputArray[], int noOfElements);
float addition(char *InputArray[], int noOfElements);
void run(char *InputArray[], int bufflen, int tokenNum);
int main()
{
    
    while (1)
    {
        char buff[100];
        write(STDOUT_FILENO, "Sandy-->", 8);
        int readReturn = read(STDIN_FILENO, buff, 100);
        int tokenNo = 1;
        for (int i = 0; i < readReturn - 2; i++)
        {
            if (buff[i] == ' ' && buff[i + 1] != ' ')
                tokenNo++;
        }
        char *InputArray[tokenNo];
        int i = 0;

        for (char *strToken = strtok(buff, " "); strToken != NULL; strToken = strtok(NULL, " "))
        {
            InputArray[i] = strToken;
            i++;
        }
        if (strcmp(InputArray[0], "add") == 0)
        {
            if (validateCommand(InputArray, tokenNo))
            {
                char displayResult[50];
                int noOfCharWrite = sprintf(displayResult, "the result is %f\n", addition(InputArray, tokenNo));
                write(STDOUT_FILENO, displayResult, noOfCharWrite);
            }
            else
            {
                write(STDOUT_FILENO, "Please enter valid ADD parameters\n", 35);
            }
        }
        else if (strcmp(InputArray[0], "run") == 0)
        {
            run(InputArray, readReturn - 4, tokenNo);
        }
    }
    return 0;
}
bool validateCommand(char *InputArray[], int noOfElements)
{
    bool runCheck = 1;
    for (int i = 1; i < noOfElements; i++)
    {
        char *token = InputArray[i];
        for (int j = 0; j < strlen(token) - 1; j++)
        {
            if (!(isdigit(token[j]) || token[j] == 10 || token[j] == 46 || (token[j] == '-' && isdigit(token[j + 1]))))
            {
                runCheck = 0;
            }
        }
    }
    return runCheck;
}

float addition(char *InputArray[], int noOfElements)
{
    float sum = 0;
    int loop = 1;
    for (loop = 1; loop < noOfElements; loop++)
    {
        sum = sum + atof(InputArray[loop]);
    }
    return sum;
}

void run(char *InputArray[], int bufflen, int tokenNum)
{
    char str[bufflen];
    strcpy(str, InputArray[1]);
    for (int i = 2; i < tokenNum; i++)
    {
        strcat(str, " ");
        strcat(str, InputArray[i]);
    }
    str[sizeof(str) - 1] = '\0';
    int pid = fork();
    if (pid > 0)
    {
        int execresult = execlp(str, " ", NULL);
        if (execresult == -1)
        {
            perror("Cannot find App");
        }else{
            write(STDOUT_FILENO,"Program is running\n",20);
        }
    }
}