#include <string.h>
#include <microhttpd.h>
#include "router.h"
#include "controller.h"
#include "respond.h"

enum MHD_Result route(void *cls,
                      struct MHD_Connection *connection,
                      const char *url,
                      const char *method,
                      const char *version,
                      const char *upload_data,
                      size_t *upload_data_size,
                      void **ptr)
{
    MHD_AccessHandlerCallback handler = NULL;

    if (0 == strcmp(url, "/"))
    {
        if (0 == strcmp(method, "OPTIONS"))
            return allow(connection, "OPTIONS, GET");
        if (0 != strcmp(method, "GET"))
            return methodNotAllowed(connection);
        if (0 != *upload_data_size)
            return MHD_NO;

        handler = &defaultHtml;
    }
    else if (0 == strcmp(url, "/json"))
    {
        if (0 == strcmp(method, "OPTIONS"))
            return allow(connection, "OPTIONS, GET");
        if (0 != strcmp(method, "GET"))
            return methodNotAllowed(connection);
        if (0 != *upload_data_size)
            return MHD_NO;

        handler = &dummyJson;
    }

    if (NULL != handler)
    {
        return (*handler)(cls, connection, url, method, version, upload_data, upload_data_size, ptr);
    }

    return notFound(connection);
}