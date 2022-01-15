#include <string.h>
#include <microhttpd.h>
#include <jansson.h>
#include "controller.h"
#include "respond.h"
#include "jsonplaceholder-api.h"

enum MHD_Result getUsersPostsWithComments(void *cls,
                                          struct MHD_Connection *connection,
                                          const char *url,
                                          const char *method,
                                          const char *version,
                                          const char *upload_data,
                                          size_t *upload_data_size,
                                          void **ptr)
{
    json_auto_t *users = fetchUsers();
    size_t n = json_array_size(users);

    int userIds[n];
    int *postIds[n];

    size_t i, j;
    json_t *user, *userPost;

    json_array_foreach(users, i, user)
    {
        userIds[i] = json_integer_value(json_object_get(user, "id"));
    }

    json_auto_t *posts = fetchUsersPosts(userIds, n);

    json_array_foreach(users, i, user)
    {
        json_object_set(user, "posts", json_array_get(posts, i));
    }

    size_t nUserPosts[n];
    json_array_foreach(users, i, user)
    {
        nUserPosts[i] = json_array_size(json_object_get(user, "posts"));
        postIds[i] = malloc(nUserPosts[i] * sizeof(int));

        json_array_foreach(json_object_get(user, "posts"), j, userPost)
        {
            postIds[i][j] = json_integer_value(json_object_get(userPost, "id"));
        }
    }

    json_auto_t *postsComments = fetchPostsComments(postIds, n, nUserPosts);
    json_array_foreach(users, i, user)
    {
        free(postIds[i]);
        json_array_foreach(json_object_get(user, "posts"), j, userPost)
        {
            __auto_type postComments = json_array_get(json_array_get(postsComments, i), j);
            json_object_set(userPost, "comments", postComments);
        }
    }

    return ok(connection, "application/json", json_dumps(users, JSON_COMPACT), MHD_RESPMEM_MUST_FREE);
}

enum MHD_Result getUsersAlbumsWithPhotos(void *cls,
                                         struct MHD_Connection *connection,
                                         const char *url,
                                         const char *method,
                                         const char *version,
                                         const char *upload_data,
                                         size_t *upload_data_size,
                                         void **ptr)
{
    json_auto_t *users = fetchUsers();
    size_t n = json_array_size(users);

    int userIds[n];
    int *albumIds[n];

    size_t i, j;
    json_t *user, *userAlbum;

    json_array_foreach(users, i, user)
    {
        userIds[i] = json_integer_value(json_object_get(user, "id"));
    }

    json_auto_t *albums = fetchUsersAlbums(userIds, n);

    json_array_foreach(users, i, user)
    {
        json_object_set(user, "albums", json_array_get(albums, i));
    }

    size_t nUserAlbums[n];
    json_array_foreach(users, i, user)
    {
        nUserAlbums[i] = json_array_size(json_object_get(user, "albums"));
        albumIds[i] = malloc(nUserAlbums[i] * sizeof(int));

        json_array_foreach(json_object_get(user, "albums"), j, userAlbum)
        {
            albumIds[i][j] = json_integer_value(json_object_get(userAlbum, "id"));
        }
    }

    json_auto_t *albumsPhotos = fetchAlbumsPhotos(albumIds, n, nUserAlbums);
    json_array_foreach(users, i, user)
    {
        free(albumIds[i]);
        json_array_foreach(json_object_get(user, "albums"), j, userAlbum)
        {
            __auto_type albumPhotos = json_array_get(json_array_get(albumsPhotos, i), j);
            json_object_set(userAlbum, "photos", albumPhotos);
        }
    }

    return ok(connection, "application/json", json_dumps(users, JSON_COMPACT), MHD_RESPMEM_MUST_FREE);
}

enum MHD_Result getUsersTodos(void *cls,
                              struct MHD_Connection *connection,
                              const char *url,
                              const char *method,
                              const char *version,
                              const char *upload_data,
                              size_t *upload_data_size,
                              void **ptr)
{
    json_auto_t *users = fetchUsers();
    size_t n = json_array_size(users);
    int userIds[n];

    size_t i;
    json_t *user;
    json_array_foreach(users, i, user)
    {
        userIds[i] = json_integer_value(json_object_get(user, "id"));
    }
    json_auto_t *todos = fetchUsersTodos(userIds, n);
    json_array_foreach(users, i, user)
    {
        json_object_set(user, "todos", json_array_get(todos, i));
    }

    return ok(connection, "application/json", json_dumps(users, JSON_COMPACT), MHD_RESPMEM_MUST_FREE);
}
