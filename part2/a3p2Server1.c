#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/*
    CONCURRENT SERVER: THREAD EXAMPLE
    Must be linked with the "pthread" library also, e.g.:
       cc -o example example.c -lnsl -lsocket -lpthread 

    This program creates a connection socket, binds a name to it, then
    listens for connections to the sockect.  When a connection is made,
    it accepts messages from the socket until eof, and then waits for
    another connection...

    This is an example of a CONCURRENT server -- by creating threads several
    clients can be served at the same time...

    This program has to be killed to terminate, or alternately it will abort in
    120 seconds on an alarm...
*/

#define PORTNUMBER 10010

struct serverParm {
           int connectionDesc;
       };

void *serverThread(void *parmPtr) {

#define PARMPTR ((struct serverParm *) parmPtr)
    int recievedMsgLen;
    char messageBuf[1025];

    FILE *log;
//    log = fopen("a3p1Server1.log", "a");

    /* Server thread code to deal with message processing */
    printf("DEBUG: connection made, connectionDesc=%d\n",
            PARMPTR->connectionDesc);
    if (PARMPTR->connectionDesc < 0) {
        printf("Accept failed\n");
        return(0);    /* Exit thread */
    }


	
    /* Receive messages from sender... */
    while ((recievedMsgLen=
            read(PARMPTR->connectionDesc,messageBuf,sizeof(messageBuf)-1)) > 0) 
    {
        recievedMsgLen[messageBuf] = '\0';
        printf("\nCommand Received: %s\n",messageBuf);
//        if (write(PARMPTR->connectionDesc,"->\n",50) < 0) {
//               perror("Server: write error");
//               return(0);
//          }

//	system(messageBuf);

	printf("Processing command...\n");
	system("date");
	system("ps | grep \"server1\"");
	

	time_t raw;
	struct tm* myTime;
	time(&raw);
	myTime = localtime(&raw);

	
	log = fopen("a3p2Server1.log", "a");
	fprintf(log, "%s", asctime(myTime));
	fprintf(log, "%s\n", messageBuf);
	fclose(log);



	const int PATH_MAX = 100;

	FILE *fp;
	char path[PATH_MAX];
//	char path[100] = "fuck\n";

//	printf("Cmd: %s\n", messageBuf);

	fp = popen(messageBuf, "r");
//	fp = popen("date", "r");
	if (fp == NULL)
	{printf("NULL!\n", 10);}

//	rewind(fp);
//	write(PARMPTR->connectionDesc, &fp, 100);

//	printf("yay\n");

//	if (fgets(path, PATH_MAX, fp) == NULL)
//	{printf("NULL!\n");}

//	int i = 0;
//	char **myBuff[50];
//	char *myBuff[50];

	char catStr[4000];
	int place = 0;

	while (fgets(path, PATH_MAX, fp) != NULL)
	{
//		printf("print me\n");
//		printf("%s", messageBuf);
//		printf("%s", path);
//		*myBuff[i] = path;
//		printf("%s",*myBuff[i] = path);
//		i++;
//		printf("%s",(*myBuff)[i++] = path);

		int current = 0;
		while (current < strlen(path) - 1)
		{
			catStr[place] = path[current];
			place++;
			current++;
		}
		catStr[place++] = ' ';


//		printf("%s", catStr);


//		printf("\nmyBuff[0] = %s", myBuff[0]);
		
//		write(PARMPTR->connectionDesc, path, 50);
//		write(PARMPTR->connectionDesc, "fuck\n", 50);
	}
	
	catStr[place] = '\0';
	printf("Result: %s\n", catStr);

//	write(PARMPTR->connectionDesc, catStr, 500);

//	printf("\nAgain, myBuff[0] = %s", myBuff[0]);

/*
	int j = 0;
	while (j < i)
	{
		printf("\n%s", (*myBuff)[j]);
		j++;
	}
*/

//	write(PARMPTR->connectionDesc, myBuff, 50);
//
	pclose(fp);
//	printf("here?\n");


        if (write(PARMPTR->connectionDesc,catStr,4000) < 0) {
	        perror("Server: write error");
		return(0);
	}





    }
  
     
    close(PARMPTR->connectionDesc);  /* Avoid descriptor leaks */
    free(PARMPTR);                   /* And memory leaks */
    return(0);                       /* Exit thread */
}

int main (int argc, char **argv) {
    int listenDesc;
    struct sockaddr_in myAddr;
    struct serverParm *parmPtr;
    int connectionDesc;
    pthread_t threadID;

    /* For testing purposes, make sure process will terminate eventually */
//    alarm(120);  /* Terminate in 120 seconds */
	alarm(180); // Terminate in 3 minutes

    /* Create socket from which to read */
    if ((listenDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("open error on socket");
        exit(1);
    }

    /* Create "name" of socket */
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = INADDR_ANY;
    // myAddr.sin_port = htons(PORTNUMBER);
    myAddr.sin_port = htons((int) strtol(argv[1], (char **)NULL, 10));
        
    if (bind(listenDesc, (struct sockaddr *) &myAddr, sizeof(myAddr)) < 0) {
        perror("bind error");
        exit(1);
    }

    /* Start accepting connections.... */
    /* Up to 5 requests for connections can be queued... */
    listen(listenDesc,5);

    while (1) /* Do forever */ {
        /* Wait for a client connection */
        connectionDesc = accept(listenDesc, NULL, NULL);

        /* Create a thread to actually handle this client */
        parmPtr = (struct serverParm *)malloc(sizeof(struct serverParm));
        parmPtr->connectionDesc = connectionDesc;
        if (pthread_create(&threadID, NULL, serverThread, (void *)parmPtr) 
              != 0) {
            perror("Thread create error");
            close(connectionDesc);
            close(listenDesc);
            exit(1);
        }

        printf("Parent ready for another connection\n");
    }

    return 0;

}
