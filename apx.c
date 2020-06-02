#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {

    int sockfd, connfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("Fail to create a socket.");
        exit(-1);
    }

    struct sockaddr_in serverInfo, clientInfo;
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo, sizeof(serverInfo));

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
    listen(sockfd, 5);

    while(1) {
        connfd = accept(sockfd, (struct sockaddr *)&clientInfo, &addrlen);

        pid_t pid = fork();      //可以同時處理多個client
        switch (pid)
        {
        case -1:
            printf("fork error.\n");
            exit(-1);
            break;

        case 0:
            printf("this is child, pid=%d\n", getpid());  //fork出來的子程序
            while(1)
            {
                char message[100] = "hello", inputBuffer[100];
                write(connfd, message, sizeof(message));
                read(connfd, inputBuffer, sizeof(inputBuffer));
                
                printf("%s\n", inputBuffer);
            }
            break;

        default:
            break;
        }
    }
}