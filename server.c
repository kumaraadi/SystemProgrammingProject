#include <pthread.h>
#include "myfunctions.h"

#define TRUE 1
#define MAX_PROCESSES 50
#define MAX_CLIENTS 20

void *writingThread(void *ptr);

int Clients_count = 0;
char input_buff[1024];
struct Client clients[50];

int main()
{
	pthread_t w;
	int wc;
	wc = pthread_create(&w, NULL, writingThread, NULL);

	int sock, length;
	struct sockaddr_in server;
	struct sockaddr client_addr;
	int lenc = sizeof(client_addr);
	int msgsock;
	char buf[1024];
	int rval;
	int i;
	char temp[500];

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("opening stream socket");
		exit(1);
	}
	/* Name socket using wildcards */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 0;
	if (bind(sock, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("binding stream socket");
		exit(1);
	}
	/* Find out assigned port number and print it out */
	length = sizeof(server);
	if (getsockname(sock, (struct sockaddr *)&server, (socklen_t *)&length))
	{
		perror("getting socket name");
		exit(1);
	}
	printf("Socket has port #%d\n", ntohs(server.sin_port));
	fflush(stdout);

	listen(sock, MAX_CLIENTS);
	do
	{
		msgsock = accept(sock, &client_addr, &lenc);
		if (msgsock == -1)
			perror("accept");
		else
		{
			struct sockaddr_in *pV4Addr = (struct sockaddr_in *)&client_addr;
			struct in_addr ipAddr = pV4Addr->sin_addr;
			char client_ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &ipAddr, client_ip, INET_ADDRSTRLEN);

			write(STDOUT_FILENO, client_ip, strlen(client_ip));
			write(STDOUT_FILENO, "\033[0;32m CONNECTED\n\033[0m", 23);
			// write(msgsock, " CONNECTED\n", 11);

			//NEW CLIENT ADDED
			time_t now = time(0);
			struct tm *ltm = localtime(&now);
			char time_curr[20];
			sprintf(time_curr, "%d:%d:%d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

			strcpy(clients[Clients_count].client_ip, client_ip);
			clients[Clients_count].msgsock = msgsock;
			strcpy(clients[Clients_count].start_time, time_curr);
			strcpy(clients[Clients_count].status, "Active");
			strcpy(clients[Clients_count].end_time, "-");
			Clients_count++;

			int pid = fork();
			if (pid == 0)
			{
				struct Process processes[30];
				int process_count = 0;
				clients[Clients_count].pro_list = processes;

				do
				{
					bzero(buf, sizeof(buf));
					if ((rval = read(msgsock, buf, 1024)) < 0)
						perror("reading stream message");
					i = 0;
					if (rval == 0)
					{
						write(STDOUT_FILENO, "Ending connection\n", 18);
						close(msgsock);
					}
					else
					{
						buf[rval - 1] = '\0';
						int tokens = 1;

						for (i = 0; i < rval - 2; i++)
						{
							if (buf[i] == ' ' && buf[i + 1] != ' ')
								tokens++;
						}
						buf[rval - 1] = '\0';
						char *TokensArray[tokens];

						char *token;
						token = strtok(buf, " ");
						int k = 0;
						while (token != NULL)
						{
							TokensArray[k] = token;
							token = strtok(NULL, " ");
							k++;
						}
						if (k == 0)
						{
							write(msgsock, "no input found!\n", 16);
						}
						else if (strcmp(TokensArray[0], "add") == 0) //ADD
						{
							int add_ret = Handle_Add(tokens, TokensArray, msgsock);
						}
						else if (strcmp(TokensArray[0], "run") == 0) //RUN
						{
							char str[100];
							int s_ret = sprintf(str, "%s running now\n", TokensArray[1]);
							int y = -1;
							int fd[2];
							int Ppip = pipe2(fd, __O_CLOEXEC);
							if (Ppip == -1)
							{
								perror("Pipe");
							}

							int pid = fork();

							if (pid == -1)
							{
								perror("client fork");
							}
							else if (pid == 0)
							{
								close(fd[0]);
								int ex_ret = execlp(TokensArray[1], TokensArray[1], NULL);
								char ret[20];
								int s = sprintf(ret, "%d", errno);
								write(fd[1], ret, s);
								exit(0);
							}
							else
							{
								close(fd[1]);
								char checkExec[100];
								y = read(fd[0], checkExec, 100);
								if (y == 0)
								{
									time_t now_ = time(0);
									struct tm *ltm_ = localtime(&now_);
									char time_curr_[20];
									sprintf(time_curr_, "%d:%d:%d", ltm_->tm_hour, ltm_->tm_min, ltm_->tm_sec);

									strcpy(processes[process_count].process_name, TokensArray[1]);
									processes[process_count].pid = pid;
									strcpy(processes[process_count].start_time, time_curr_);
									strcpy(processes[process_count].status, "Active");
									strcpy(processes[process_count].end_time, "-");
									process_count++;
									clients[Clients_count].count = clients[Clients_count].count + 1;
									write(msgsock, str, s_ret);
								}
								else
								{
									write(msgsock, "program not found!\n", 19);
								}
							}
							process_count++;
						}
						else if (strcmp(TokensArray[0], "list") == 0) //Processes's list
						{
							if (process_count == 0)
							{
								write(msgsock, "List empty!\n", 12);
							}
							else
							{
								write(msgsock, "Processes:\n", 11);

								for (i = 0; i < process_count - 1; i++)
								{
									write(msgsock, "\n", 1);
									write(msgsock, processes[i].process_name, strlen(processes[i].process_name));
									write(msgsock, "\n", 1);
									char str[20];
									sprintf(str, "%d", processes[i].pid);
									write(msgsock, str, strlen(str));
									write(msgsock, "\n", 1);
									write(msgsock, processes[i].status, strlen(processes[i].status));
									write(msgsock, "\n", 1);
									write(msgsock, processes[i].start_time, strlen(processes[i].start_time));
									write(msgsock, "\n", 1);
									write(msgsock, processes[i].end_time, strlen(processes[i].end_time));
									write(msgsock, "\n", 1);
									write(msgsock, "\n", 1);
								}
							}
						}else if(strcmp(TokensArray[0], "kill") == 0){
							if(kill(atoi(TokensArray[1]), SIGTERM)==0){
								
								write(msgsock, "Success!\n", 9);
							}else{
								perror("kill");
							}
						}
						else if (strcmp(TokensArray[0], "exit") == 0)
						{
							write(msgsock, "Bye\n", 4);
							time_t now_ = time(0);
							struct tm *ltm_ = localtime(&now_);
							char time_curr_[20];
							sprintf(time_curr_, "%d:%d:%d", ltm_->tm_hour, ltm_->tm_min, ltm_->tm_sec);

							for (i = 0; i < process_count; i++)
							{
								strcpy(processes[i].end_time, time_curr_);
								strcpy(processes[i].status, "Inactive");
							}
							return 0;
						}
						else
						{
							write(msgsock, "Invalid Command\n", 16);
						}
					}

				} while (rval != 0);
			}
		}

	} while (TRUE);
}

void *writingThread(void *ptr)
{
	while (1)
	{
		int i = 0;
		int r_ret = read(STDIN_FILENO, input_buff, 1024);

		input_buff[r_ret - 1] = '\0';
		if (input_buff[0] == '\0')
		{
			write(STDOUT_FILENO, "Invalid Command\n", 16);
		}
		else
		{
			int tokens = 1;

			for (i = 0; i < r_ret - 2; i++)
			{
				if (input_buff[i] == ' ' && input_buff[i + 1] != ' ')
					tokens++;
			}
			input_buff[r_ret - 1] = '\0';
			char *TokensArray[tokens];

			char message[1024];
			if (r_ret > 7)
			{
				strcpy(message, input_buff);
				// write(STDOUT_FILENO, message + 8, strlen(message+8));
			}
			char *token;
			token = strtok(input_buff, " ");
			i = 0;
			while (token != NULL)
			{
				TokensArray[i] = token;
				token = strtok(NULL, " ");
				i++;
			}

			if (strcmp(TokensArray[0], "list") == 0)
			{
				if (Clients_count == 0)
				{
					write(STDOUT_FILENO, "List empty!\n", 12);
				}
				else
				{
					char str2[20];
					for (i = 0; i < Clients_count; i++)
					{
						write(STDOUT_FILENO, clients[i].client_ip, strlen(clients[i].client_ip));
						write(STDOUT_FILENO, "\n", 1);
						int rrr = sprintf(str2, "%d", clients[i].msgsock);
						write(STDOUT_FILENO, str2, rrr);
						write(STDOUT_FILENO, "\n", 1);
						write(STDOUT_FILENO, clients[i].status, strlen(clients[i].status));
						write(STDOUT_FILENO, "\n", 1);
						write(STDOUT_FILENO, clients[i].start_time, strlen(clients[i].start_time));
						write(STDOUT_FILENO, "\n", 1);
						write(STDOUT_FILENO, clients[i].end_time, strlen(clients[i].end_time));
						write(STDOUT_FILENO, "---\n", 4);
					}
				}
			}
			else if (strcmp(TokensArray[0], "message") == 0)
			{
				if (strcmp(TokensArray[1], "-all") == 0)
				{
					if (r_ret < 15)
					{
						write(STDOUT_FILENO, "No message found!\n", 18);
					}
					else
					{
						for (i = 0; i < Clients_count; i++)
						{
							write(clients[i].msgsock, message + 13, strlen(message + 13));
						}
					}
				}
				else
				{
					if (r_ret < 16)
					{
						write(STDOUT_FILENO, "Invalid Argument\n", 17);
					}
					else
					{
						for (i = 0; i < Clients_count; i++)
						{
							if (strcmp(clients[i].client_ip, TokensArray[1]) == 0)
							{
								break;
							}
							else
							{
								continue;
							}
						}
						if (i == Clients_count)
						{
							write(STDOUT_FILENO, "Client not found!\n", 18);
						}
						else
						{
							write(clients[i].msgsock, message + 8, strlen(message + 8));
							write(clients[i].msgsock, "\n", 1);
						}
					}
				}
			}
			else if (strcmp(TokensArray[0], "kill") == 0)
			{
				if (strcmp(TokensArray[1], "-all") == 0)
				{
					//SEND KILL SIGNAL TO ALL
				}
				else
				{
					for (i = 0; i < Clients_count; i++)
					{
						if (strcmp(clients[i].client_ip, TokensArray[1]) == 0)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					if (i == Clients_count)
					{
						write(STDOUT_FILENO, "Client not found!\n", 18);
					}
					else
					{
						write(clients[i].msgsock, message + 8, strlen(message + 8));
						write(clients[i].msgsock, "\n", 1);
					}
				}
			}
			else if (strcmp(TokensArray[0], "list-all") == 0)
			{
				int j;
				for (i = 0; i < Clients_count; i++)
				{
					write(STDOUT_FILENO, clients[i].client_ip, strlen(clients[i].client_ip));
					write(STDOUT_FILENO, clients[i].pro_list[0].process_name, strlen(clients[i].pro_list[0].process_name));
					for (j = 0; j < clients[i].count; j++)
					{
						write(STDOUT_FILENO, "\n", 1);
						write(STDOUT_FILENO, clients[i].pro_list[j].process_name, strlen(clients[i].pro_list[j].process_name));
						write(STDOUT_FILENO, "\n", 1);
						// char str[20];
						// sprintf(str, "%d", processes[i].pid);
						// write(STDOUT_FILENO, str, strlen(str));
						// write(STDOUT_FILENO, "\n", 1);
						// write(STDOUT_FILENO, processes[i].status, strlen(processes[i].status));
						// write(STDOUT_FILENO, "\n", 1);
						// write(STDOUT_FILENO, processes[i].start_time, strlen(processes[i].start_time));
						// write(STDOUT_FILENO, "\n", 1);
						// write(STDOUT_FILENO, processes[i].end_time, strlen(processes[i].end_time));
						write(STDOUT_FILENO, "\n", 1);
						write(STDOUT_FILENO, "\n", 1);
					}
				}
			}
			else if (strcmp(TokensArray[0], "clear") == 0)
			{
				system("clear");
			}
			else
			{
				write(STDOUT_FILENO, "Invalid Command\n", 16);
			}
		}
	}
}
