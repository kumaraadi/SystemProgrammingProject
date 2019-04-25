#include "myfunctions.h"

#define TRUE 1
#define MAX_PROCESSES 50
#define MAX_CLIENTS 20

int main()
{
	Clients *head = NULL;
	head = malloc(sizeof(Clients));
	int Clients_count = 0;

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

			// write(STDOUT_FILENO, client_ip, strlen(client_ip));

			int pid = fork();

			if (pid == 0)
			{
				Processes *head = NULL;
				head = malloc(sizeof(Processes));

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
						i = 0;
						while (token != NULL)
						{
							TokensArray[i] = token;
							token = strtok(NULL, " ");
							i++;
						}
						if (strcmp(TokensArray[0], "add") == 0) //ADD
						{
							int add_ret = Handle_Add(tokens, TokensArray, msgsock);
						}
						else if (strcmp(TokensArray[0], "run") == 0) //RUN
						{
							int run_ret = Handle_run(TokensArray, head);
							int s_ret = sprintf(temp, "PID = %i\n", run_ret);
							write(msgsock, temp, s_ret);
						}
						else if (strcmp(TokensArray[0], "list") == 0)
						{
							showProcesses(head, msgsock);
							write(msgsock, "\n", 1);
						}

						else if (strcmp(TokensArray[0], "exit") == 0)
						{
							write(msgsock, "Bye\n", 4);
							exit(1);
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
