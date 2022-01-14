#pragma once
#include <microhttpd.h>

enum MHD_Result defaultHtml(void *,
                            struct MHD_Connection *,
                            const char *,
                            const char *,
                            const char *,
                            const char *,
                            size_t *,
                            void **);

enum MHD_Result dummyJson(void *,
                          struct MHD_Connection *,
                          const char *,
                          const char *,
                          const char *,
                          const char *,
                          size_t *,
                          void **);
