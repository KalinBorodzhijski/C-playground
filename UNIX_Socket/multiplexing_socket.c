#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8888
#define MAX_CLIENTS 5

int main() {
    int sockfd, newsockfd, max_sd, activity, i, valread;
    int client_socket[MAX_CLIENTS];
    char buffer[1025];
    fd_set readfds;

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    for (i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    puts("Waiting for connections ...");

    while(1) {
        FD_ZERO(&readfds);

        FD_SET(sockfd, &readfds);
        max_sd = sockfd;

        for (i = 0 ; i < MAX_CLIENTS ; i++) {
            int sd = client_socket[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        if (FD_ISSET(sockfd, &readfds)) {
            if ((newsockfd = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection, socket fd is %d, ip is: %s, port: %d\n", newsockfd, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = newsockfd;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                if ((valread = read(sd, buffer, 1024)) == 0) {
                    getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    printf("Host disconnected, ip %s, port %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    close(sd);
                    client_socket[i] = 0;
                }

                else {
                    buffer[valread] = '\0';
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }

    return 0;
}
