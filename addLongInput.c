#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define buff_size 20
struct Node
{
    char data[10];
    struct Node *next;
};
// void printList(struct Node *n)
// {
//     while (n != NULL)
//     {

//         printf(" %s ", n->data);
//         n = n->next;
//     }
// }
int main()
{
    struct Node *head = NULL;
    struct Node *current = NULL;
    struct Node *temp = NULL;
    struct Node *r_head = NULL;
    struct Node *r_current = NULL;
    int sum = 0;
    char *buff = (char *)malloc(buff_size);
    char buff2[buff_size];
    bool validated = true;

    while (1)
    {
        write(STDOUT_FILENO, "Input: ", 7);
        int r = 1, t = 1;

        while (buff[r - 1] != '\n')
        {
            r = read(STDIN_FILENO, buff, buff_size);
            if (buff[r - 1] != '\n')
            {
                t++;
                buff = (char *)realloc(buff, t * buff_size);
            }
        }
        validated = true;
        buff[r - 1] = '\0';
        strcpy(buff2, buff);

        buff[0] = buff2[0];
        buff[1] = '\n';
        int k = 1;
        int i;
        for (i = 1; i < r; i++)
        {
            if (buff2[i] != ';')
            {
                buff[k] = buff2[i];
                buff[k + 1] = '\n';
                k++;
            }
            else
            {
                buff[k] = ' ';
                buff[k + 1] = ';';
                buff[k + 2] = ' ';
                k = k + 3;
                buff[k + 4] = '\n';
            }
        }

        for (i = 0; i < r - 1; i++)
        {
            if (isdigit(buff[i]) || buff[i] == ' ' || buff[i] == ';')
            {
                continue;
            }
            else
            {
                write(STDOUT_FILENO, "Invalid input\n\n", 15);
                validated = false;
                break;
            }
        }
        if (validated)
        {
            char *token = strtok(buff, " ");
            while (token != NULL)
            {

                if (head == NULL)
                {
                    head = (struct Node *)malloc(sizeof(struct Node));
                    strcpy(head->data, token);
                    current = head;
                }
                else
                {
                    struct Node *newNode = NULL;
                    newNode = (struct Node *)malloc(sizeof(struct Node));
                    strcpy(newNode->data, token);
                    current->next = newNode;
                    current = newNode;
                }
                token = strtok(NULL, " ");
            }
            if (r_head == NULL)
            {
                r_head = head;
            }

            temp = r_head;
            while (temp != NULL)
            {
                r_current = r_head;
                if (strcmp(temp->data, ";") == 0)
                {
                    while (r_current != temp)
                    {
                        sum = sum + atoi(r_current->data);
                        r_current = r_current->next;
                    }
                    char res[5];
                    int ret = sprintf(res, "Sum: %d\n", sum);
                    write(STDOUT_FILENO, res, ret);
                    sum = 0;

                    if (r_current->next != NULL)
                    {
                        r_head = r_current->next;
                        temp = temp->next;
                        head = r_head;
                    }
                    else
                    {
                        temp = NULL;
                        r_head = NULL;
                        head = NULL;
                    }
                }
                else
                {
                    temp = temp->next;
                }
            }
            write(STDOUT_FILENO, "\n\n", 2);
        }
    }
    return 0;
}
