#include <stdio.h>
#include <microhttpd.h>
#include "server.h"
#include "router.h"

struct MHD_Daemon *start(int port, int threadPoolSize)
{
    return MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                            port,
                            NULL,
                            NULL,
                            route,
                            NULL,
                            MHD_OPTION_THREAD_POOL_SIZE, threadPoolSize,
                            MHD_OPTION_END);
}

void stop(struct MHD_Daemon *d)
{
    MHD_stop_daemon(d);
}
