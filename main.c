#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "server.h"
#include "jsonplaceholder-api.h"

static struct MHD_Daemon *server = NULL;

static int setup(int port, int threadPoolSize)
{
    init();
    server = start(port, threadPoolSize);
    return server != NULL ? 1 : 0;
}

static void teardown(int signalNumber)
{
    stop(server);
    cleanup();
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

    if (setup(port, threadPoolSize) == 0)
        return 1;

    signal(SIGINT, teardown);
    signal(SIGTERM, teardown);
    pause();

    return 0;
}
