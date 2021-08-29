#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 255
#define FILENAME "./file.txt"
#define CLIENT_FILENAME "./file1.txt"

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
    struct sockaddr_un client = {0};

    socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        error_macro("SOCKET CREATE");
    }

    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, FILENAME, sizeof(server.sun_path) - 1);

    client.sun_family = AF_LOCAL;
    strncpy(client.sun_path, CLIENT_FILENAME, sizeof(client.sun_path) - 1);

    if (bind(socket_fd, (struct sockaddr *)&client, sizeof(struct sockaddr_un)) == -1)
    {
        error_macro("BIND TO SOCKET");
    }

    server_size = sizeof(struct sockaddr_un);
    do
    {
        bzero(buf, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        char *p = strchr(buf, '\n');
        if (p != NULL)
        {
            buf[strlen(buf) - 1] = '\0';
        }

        if (sendto(socket_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&server,
            server_size) == -1)
        {
            error_macro("SEND ERROR");
        }

        if (recvfrom(socket_fd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
        {
            error_macro("RECV ERROR");
        }

        printf("Received message - %s\n", buf);
    } while (strncmp(buf, "exit", 255) != 0);

    close(socket_fd);

    if (remove(CLIENT_FILENAME) == -1)
    {
        error_macro("CLIENT FILENAME");
    }

    return 0;
}
