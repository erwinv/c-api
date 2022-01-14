#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "server.h"

static struct MHD_Daemon *server = NULL;

static void exitHandler(int signalNumber)
{
    stop(server);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("%s PORT THREADPOOL_SIZE\n",
               argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int threadPoolSize = argc == 2 ? 1 : atoi(argv[2]);

    server = start(port, threadPoolSize);
    if (server == NULL)
        return 1;

    signal(SIGINT, exitHandler);
    signal(SIGTERM, exitHandler);
    pause();

    return 0;
}
