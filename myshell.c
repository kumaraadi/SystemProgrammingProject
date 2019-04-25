#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

float add(char *arr[], int n);
int validate(char *arr[], int n);

// struct Node
// {
//     char data[10];
//     struct Node *next;
// };
int main()
{
    bool check_exit = false;
    int size_of_buffer = 100;
    char buff[size_of_buffer];
    char initial_display[100] = "Welcome,\nEnter numbers with spaces to add them.\n\n";
    char ask_input[8] = ">";
    int result;
    char a = '0';
    int tokens = 1;
    int i = 0;

    write(STDOUT_FILENO, initial_display, 100);

    do
    {
        result = 0;
        tokens = 1;
        write(STDOUT_FILENO, ask_input, 1);
        int no = read(STDIN_FILENO, buff, size_of_buffer);

        for (i = 0; i < no - 2; i++)
        {
            if (buff[i] == ' ' && buff[i + 1] != ' ')
                tokens++;
        }
        buff[no - 1] = '\0';
        char *TokensArray[tokens];

        char *token;
        token = strtok(buff, " ");
        i = 0;
        while (token != NULL)
        {
            TokensArray[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        if (strcmp(TokensArray[0], "add") == 0)
        {
            if (tokens > 1)
            {
                if (validate(TokensArray, tokens) == 1)
                {
                    float result = add(TokensArray, tokens);
                    write(STDOUT_FILENO, "Sum: ", 5);
                    int s = sprintf(buff, "%f\n\n", result);
                    write(STDOUT_FILENO, buff, s);
                    result = -1;
                }
                else
                {
                    write(STDOUT_FILENO, "non-numeric can't be added!\n", 28);
                }
            }
            else
            {
                write(STDOUT_FILENO, "No number to add! Try again.\n", 29);
            }
        }
        else if (strcmp(TokensArray[0], "run") == 0)
        {
            write(STDOUT_FILENO, "run\n", 4);
            int pid = fork();

            if (pid == 0)
            {
                execvp("gedit", NULL);
            }
        }

        else if (strcmp(TokensArray[0], "exit") == 0)
        {
            write(STDOUT_FILENO, "Bye\n", 4);
            check_exit = true;
        }
        else
        {
            write(STDOUT_FILENO, "Invalid Command\n", 16);
        }

    } while (!check_exit);
    return 0;
}
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
