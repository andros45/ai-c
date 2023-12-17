#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    const char *url = "www.example.com";
    const char *request_template = "GET / HTTP/1.1\r\nHost: %s\r\n\r\n";

    // Skapa en socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket");

    // Hämta adressinformation för servern
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(url, "http", &hints, &server_info) != 0)
        error("Error getting server address");

    // Anslut till servern
    if (connect(sockfd, server_info->ai_addr, server_info->ai_addrlen) < 0)
        error("Error connecting to server");

    // Skicka HTTP-förfrågan
    char request[MAX_BUFFER_SIZE];
    snprintf(request, MAX_BUFFER_SIZE, request_template, url);
    if (send(sockfd, request, strlen(request), 0) < 0)
        error("Error sending request");

    // Ta emot och skriva ut svaret
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    if (bytes_received < 0)
        error("Error receiving response");

    // Stäng socket och frigör resurser
    close(sockfd);
    freeaddrinfo(server_info);

    return 0;
}
