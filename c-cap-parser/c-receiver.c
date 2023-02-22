/*
    Compiles with:  gcc -Wall -I/usr/include/libxml -o c-receiver.o c-receiver.c -lxml2
    Runs with:      ./c-receiver
*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "capparser.c"

#define PORT 9090

char* read_all(int new_socket);

int main(int argc, char const* argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 9090
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 9090
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char* res = read_all(new_socket);

    Data data = parseFromString(res);
    Frequency *temp = data.frequency;
    while (temp)
    {
        printf("Name: %s, Frequency: %s\n", temp->name, temp->frequency);
        temp = temp->next;
    }
    printf("mimeType: %s\nAudio: %s\n", data.audio->mimeType, data.audio->bytes);

    free(res);
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}

char* read_all(int new_socket) {
    int n = 1024;
    char* res = malloc(1); // allocate memory for an empty string
    *res = '\0'; // make sure the string is null-terminated
    char buffer[1024] = { 0 };
    while (n == 1024) {
        n = read(new_socket, buffer, 1024);
        if (n > 0) {
            buffer[n] = '\0'; // make sure the received data is null-terminated
            char* new_res = realloc(res, strlen(res) + n + 1); // allocate more memory for the new data
            if (new_res == NULL) {
                free(res);
                return NULL; // handle memory allocation errors
            }
            res = new_res;
            strcat(res, buffer); // append the new data to the string
        }
    }
    return res;
}
