#include "myfunctions.h"
int main(){

    char *TokensArray[5];
    Processes* head = NULL; 
    head = malloc(sizeof(Processes));

    Processes* temp = head; 
    char tmp[20] = "Process1\0";
    
    strcpy(head->process_name, tmp);
    head->pid =  5;
    head->next = NULL;

    printf("%s\n", head->process_name);
    // printf("%i\n", head->pid);


    


    
    
    
}
