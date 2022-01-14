#pragma once
#include <microhttpd.h>

int methodNotAllowed(struct MHD_Connection *);
int allow(struct MHD_Connection *, const char *);
int notFound(struct MHD_Connection *);
int ok(struct MHD_Connection *, const char *contentType, const char *buffer, enum MHD_ResponseMemoryMode);
