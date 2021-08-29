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
    socklen_t client_socket_fd_size = 0;

    struct sockaddr_un server = {0};
    struct sockaddr_un client = {0};

    socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
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

    client_socket_fd_size = sizeof(struct sockaddr_un);
    do
    {
        if (recvfrom(socket_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client,
            &client_socket_fd_size) == -1)
        {
            error_macro("RECVFROM ERROR");
        }

        printf("Received Message - %s\n", buf);

        bzero(buf, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            buf[strlen(buf) - 1] = '\0';
        }

        if (sendto(socket_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client,
            client_socket_fd_size) == -1)
        {
            error_macro("SENDTO ERROR");
        }

    } while (strncmp(buf, "exit", 255) != 0);

    close(socket_fd);

    if (remove(FILENAME) == -1)
    {
        error_macro("CLIENT FILENAME");
    }

    return 0;
}
