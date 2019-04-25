#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *writingThread(void *ptr);

int sock;
char buf[1024];
char buff[1024];
int main(int argc, char *argv[])
{

	struct sockaddr_in server;
	struct hostent *hp;

	pthread_t w;
	int wc;
	wc = pthread_create(&w, NULL, writingThread, NULL);

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("opening stream socket");
		exit(1);
	}
	/* Connect socket using name specified by command line. */
	server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);
	if (hp == 0)
	{
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}
	bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
	server.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("connecting stream socket");
		exit(1);
	}

	while (1)
	{
		int r_val = read(sock, buf, 1024);
		if (r_val > 0)
		{
			write(STDOUT_FILENO, buf, r_val);
		}
	}
	close(sock);
}
void *writingThread(void *ptr)
{
	while (1)
	{
		write(STDOUT_FILENO, "-->", 3);
		int r_ret = read(STDIN_FILENO, buff, 1024);

		if (write(sock, buff, r_ret) < 0)
			perror("writing on stream socket");
	}
}