#include <string.h>
#include <microhttpd.h>
#include <jansson.h>
#include "controller.h"
#include "respond.h"

static const char *page = "<html><head><title>libmicrohttpd demo</title>"
                          "</head><body>libmicrohttpd demo</body></html>";

enum MHD_Result defaultHtml(void *cls,
                            struct MHD_Connection *connection,
                            const char *url,
                            const char *method,
                            const char *version,
                            const char *upload_data,
                            size_t *upload_data_size,
                            void **ptr)
{
    return ok(connection, "text/html", page, MHD_RESPMEM_PERSISTENT);
}

enum MHD_Result dummyJson(void *cls,
                          struct MHD_Connection *connection,
                          const char *url,
                          const char *method,
                          const char *version,
                          const char *upload_data,
                          size_t *upload_data_size,
                          void **ptr)
{
    json_auto_t *data = json_object();

    json_object_set_new(data, "boolean true", json_true());
    json_object_set_new(data, "boolean false", json_false());
    json_object_set_new(data, "null", json_null());
    json_object_set_new(data, "string", json_string("foo"));
    json_object_set_new(data, "number integer", json_integer(42));
    json_object_set_new(data, "number float", json_real(3.14156));

    __auto_type arr = json_array();
    for (int i = 0; i < 10; i++)
    {
        json_array_append_new(arr, json_integer(i));
    }
    json_object_set_new(data, "array", arr);

    json_object_set_new(data, "nested", json_copy(data));

    return ok(connection, "application/json", json_dumps(data, JSON_COMPACT), MHD_RESPMEM_MUST_FREE);
}
