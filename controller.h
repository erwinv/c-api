#pragma once
#include <microhttpd.h>

enum MHD_Result getRoutes(void *,
                          struct MHD_Connection *,
                          const char *,
                          const char *,
                          const char *,
                          const char *,
                          size_t *,
                          void **);

enum MHD_Result getUsersPostsWithComments(void *,
                                          struct MHD_Connection *,
                                          const char *,
                                          const char *,
                                          const char *,
                                          const char *,
                                          size_t *,
                                          void **);

enum MHD_Result getUsersAlbumsWithPhotos(void *,
                                         struct MHD_Connection *,
                                         const char *,
                                         const char *,
                                         const char *,
                                         const char *,
                                         size_t *,
                                         void **);

enum MHD_Result getUsersTodos(void *,
                              struct MHD_Connection *,
                              const char *,
                              const char *,
                              const char *,
                              const char *,
                              size_t *,
                              void **);
