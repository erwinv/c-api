#include <string.h>
#include <microhttpd.h>
#include "respond.h"

int methodNotAllowed(struct MHD_Connection *connection)
{
    __auto_type response = MHD_create_response_from_buffer(0, "", MHD_RESPMEM_PERSISTENT);
    __auto_type ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
    MHD_destroy_response(response);
    return ret;
}

int allow(struct MHD_Connection *connection, const char *methods) {
    __auto_type response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Allow", methods);
    __auto_type ret = MHD_queue_response(connection, MHD_HTTP_NO_CONTENT, response);
    MHD_destroy_response(response);
    return ret;
}

int notFound(struct MHD_Connection *connection)
{
    __auto_type response = MHD_create_response_from_buffer(0, "", MHD_RESPMEM_PERSISTENT);
    __auto_type ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

int ok(struct MHD_Connection *connection, const char *contentType, const char *buffer, enum MHD_ResponseMemoryMode memMode)
{
    __auto_type response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, memMode);
    MHD_add_response_header(response, "Content-Type", contentType);
    __auto_type ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}
