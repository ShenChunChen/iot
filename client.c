#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("Fail to create a socket.");
        exit(-1);
    }

    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8700);

    int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
    if (err == -1)
    {
        printf("Connection error");
    }

    char message[100], msg[100];
    while(1) {
        scanf("%s", message);
        write(sockfd, message, sizeof(message));
        read(sockfd, msg, sizeof(msg));
        printf("%s\n", msg);
    }
}