#pragma once
#include <microhttpd.h>

struct MHD_Daemon *start(int port, int threadPoolSize);
void stop(struct MHD_Daemon *);
