#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 255
#define FILENAME "./file.txt"

void error_macro(const char *error)
{
    perror(error);
    exit(1);
}

int main(void)
{
    char buf[BUF_SIZE] = {0};

    int socket_fd = 0;
    int client_socket_fd = 0;
    socklen_t client_socket_fd_size = 0;

    struct sockaddr_un server = {0};
    struct sockaddr_un client = {0};

    socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        error_macro("SOCKET CREATE");
    }

    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, FILENAME, sizeof(server.sun_path) - 1);

    if (bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) == -1)
    {
        error_macro("BIND TO SOCKET");
    }

    if (listen(socket_fd, 5) == -1)
    {
        error_macro("LISTEN");
    }

    client_socket_fd_size = sizeof(struct sockaddr_un);

    client_socket_fd = accept(socket_fd, (struct sockaddr *)&client, &client_socket_fd_size);
    if (client_socket_fd == -1)
    {
        error_macro("ACCEPT ERROR");
    }

    do
    {
        if (recv(client_socket_fd, buf, BUF_SIZE, 0) == -1)
        {
            error_macro("RECV ERROR");
        }

        printf("Received Message - %s\n", buf);

        bzero(buf, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            buf[strlen(buf) - 1] = '\0';
        }

        if (send(client_socket_fd, buf, BUF_SIZE, 0) == -1)
        {
            error_macro("SEND ERROR");
        }

    } while (strncmp(buf, "exit", 255) != 0);

    close(client_socket_fd);
    close(socket_fd);

    if (remove(FILENAME) == -1)
    {
        error_macro("FILE");
    }

    return 0;
}
