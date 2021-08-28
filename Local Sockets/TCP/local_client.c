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
    socklen_t server_size = 0;

    struct sockaddr_un server = {0};

    socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        error_macro("SOCKET CREATE");
    }

    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, FILENAME, sizeof(server.sun_path) - 1);

    server_size = sizeof(struct sockaddr_un);
    if (connect(socket_fd, (struct sockaddr *)&server, server_size) == -1)
    {
        error_macro("CONNECT ERROR");
    }

    do
    {
        bzero(buf, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            buf[strlen(buf) - 1] = '\0';
        }

        if (send(socket_fd, buf, BUF_SIZE, 0) == -1)
        {
            error_macro("SEND ERROR");
        }

        if (recv(socket_fd, buf, BUF_SIZE, 0) == -1)
        {
            error_macro("RECV ERROR");
        }

        printf("Received message - %s\n", buf);
    } while (strncmp(buf, "exit", 255) != 0);

    close(socket_fd);

    return 0;
}
