#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdbool.h>

#define MAXLINE 4096 /*max text line length*/
// #define SERV_PORT 10010 /*port*/

int count = 0;

int main(int argc, char **argv) 
{
	int sockfd;
	struct sockaddr_in servaddr;
//	char sendline[MAXLINE], recvline[MAXLINE];
//	char sendline[MAXLINE];
	char recvline[MAXLINE];
//	char **recvline[50];


	FILE *log;
	log = fopen("a3p3Client1.log", "a");

	// alarm(300);  // to terminate after 300 seconds
	
	//basic check of the arguments
	//additional checks can be inserted
	if (argc !=3) {
		perror("Usage: TCPClient <Server IP> <Server Port>"); 
		exit(1);
	}
	
	//Create a socket for the client
	//If sockfd<0 there was an error in the creation of the socket
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		perror("Problem in creating the socket");
		exit(2);
	}
	
	//Creation of the socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr= inet_addr(argv[1]);
	servaddr.sin_port =  htons((int) strtol(argv[2], (char**)NULL, 10)); 
	// servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
	//Connection of the client to the socket 
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
		perror("Problem in connecting to the server");
		exit(3);
	}
	



/*
 * =================================================================================
 *
 *
 *
 * PART 3 - CLIENT 1
 *
 * EDITING FUNCTIONALITY: CLIENT ASKS FOR INPUT ONCE ONLY
 * CLIENT THEN LOOPS THIS REQUEST ~8 TIMES (~15 SECONDS)
 *
 *
 * INPUT: "date; ls -l junk.txt; touch junk.txt; ls-l junk.txt"
 * SLEEP 2
 *
 *
 *
 * =================================================================================
 */




/*
	bool loop = true;

	while ((loop) && (fgets(sendline, MAXLINE, stdin) != NULL)) {
	
		char recvline[MAXLINE];
		

//		send(sockfd, sendline, strlen(sendline), 0);
		
//		printf(sendline);
//		printf(sendline);
//		printf(sendline);

	if (strcmp(sendline, "exit\n") == 0)
	{
		loop = false;
//		printf("QUIT\n\n\n\n");
	}
*/

//	else


	int counter = 1;
//	fgets(sendline, MAXLINE, stdin);


	printf("Looping: \"date; ls -l junk.txt; touch junk.txt; ls-l junk.txt\"\n");

	char sendline[MAXLINE] = "date; ls -l junk.txt; touch junk.txt; ls-l junk.txt";



	while (counter <= 5)
	{
		send(sockfd, sendline, strlen(sendline), 0);

		if (recv(sockfd, recvline, MAXLINE,0) == 0){
			//error: server terminated prematurely
			perror("The server terminated prematurely"); 
			exit(4);
		}




		// printf("%s", "String received from the server: ");
		// My modification:
		printf("%s", "Server:\n");



/*
		const int PATH_MAX = 100;

		FILE *fp;
		char path[PATH_MAX];

		fp = fopen(recvline, "r");
printf("1\n");
		if (fp == NULL)
		{printf("NULL!\n");}
		else
		{

printf("2\n");
		while (fgets(path, PATH_MAX, fp) != NULL)
		{
			printf("%s", path);
		}
printf("3\n");	
		}
		fclose(fp);
		

		}
*/

//		if (count)
//		{

/*
			printf("here\n");


			int i = 0;
			while ((*recvline)[i] != NULL)
			{
				printf("HERE AGAIN\n");
				printf("%s\n", (*recvline)[i]);
				printf("NOT ANYMORE\n");
				i++;
			}

			printf("and gone\n");
*/

//		}

//		count++;
		printf("Results: %s\n", recvline);
//		fputs(recvline, stdout);
	
//		printf("Again: %s\n", recvline);	
		
//		log = fopen("a3p1Client1.log", "a");
		fprintf(log, "%s", recvline);
//		fclose(log);	

//		int secs3 = 3000000;
		int secs2 = 2000000;

		usleep(secs2);
		counter++;


//		fclose(log);
//	        printf("Logging off...\n");
		system("date");
		system("ps | grep \"client1\"");
		printf("\n");


//		printf("Final: %s\n", recvline);
//		recvline[0] = '\0';

//	}

//		printf("I wonder... %s\n", recvline);

	}

//	fclose(log);
	printf("Logging off...\n");
	system("date");
	system("ps | grep \"client1\"");
	

	exit(0);
}
