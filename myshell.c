#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ProcessStruct 
{
	char string[50];
};

int main()
{
    bool check_exit = false;
    int size_of_buffer = 100;
    char buff[size_of_buffer];
    char initial_display[100] = "Welcome,\nEnter numbers with spaces to add them.\n\n";
    char ask_input[8]=">";
    int result;
    char a = '0';

    write(STDOUT_FILENO, initial_display, 100);

    do{
        result = 0;
            write(STDOUT_FILENO, ask_input, 1);
            int no = read(STDIN_FILENO, buff, size_of_buffer); 
            
            char *token;
            token = strtok(buff, " ");
            
            
            

            if(strcmp(token,"add")==0){
                if(no > 1){
                token = strtok(NULL, " ");
                
                    while( token != NULL ) {
                        result = atoi(token) + result;
                        token = strtok(NULL, " ");
                    }
                    write(STDOUT_FILENO, "Sum: ",5);
                    int s = sprintf(buff,"%d\n\n", result);
                    write(STDOUT_FILENO, buff, s);
                    result = -1;
                }else{
                    write(STDOUT_FILENO, "No number to add! Try again.\n",29);
                }

                
            }
                
            
            
            
            else if(strcmp(token,"run")==0){
                write(STDOUT_FILENO, "run\n",4);
                int pid = fork();

	            if ( pid == 0 ) {
		        execvp( "gedit", NULL);
	            }

	
	    
            }

            else if(strcmp(token,"exit")==0){
                write(STDOUT_FILENO, "Bye",3);
                check_exit = true;
            }else{
                write(STDOUT_FILENO, "Invalid Command\n",16);
            }
			
    }while(!check_exit);
       return 0;
}