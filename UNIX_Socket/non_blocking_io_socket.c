#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888

int main() {
    int sockfd, flags;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addrlen = sizeof(cli_addr);
    char buffer[1024];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &addrlen);
    if (connfd < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    if ((flags = fcntl(connfd, F_GETFL, 0)) < 0) {
        perror("Error getting flags");
        exit(EXIT_FAILURE);
    }
    if (fcntl(connfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Error setting non-blocking flag");
        exit(EXIT_FAILURE);
    }

    int read_bytes = read(connfd, buffer, sizeof(buffer));
    if (read_bytes < 0) {
        if (errno == EWOULDBLOCK) {
            printf("No data available to read\n");
        } else {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Received data: %s\n", buffer);
    }

    close(connfd);
    close(sockfd);
    return 0;
}
