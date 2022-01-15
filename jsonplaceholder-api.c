#include <stdio.h>
#include <curl/curl.h>
#include "jsonplaceholder-api.h"
#include <jansson.h>

void init()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void cleanup()
{
    curl_global_cleanup();
}

struct json_t *fetchUsers()
{
    char *fptr;
    size_t fsize;

    FILE *wstream = open_memstream(&fptr, &fsize);
    if (NULL == wstream)
        return json_null();

    __auto_type handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, "https://jsonplaceholder.typicode.com/users");
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, wstream);
    curl_easy_perform(handle);
    curl_easy_cleanup(handle);

    fclose(wstream);

    return json_loadb(fptr, fsize, 0, NULL);
}

struct json_t *fetchUsersPosts(int userIds[], size_t n)
{
    CURL *handles[n];
    char *fptrs[n];
    size_t fsizes[n];
    FILE *wstreams[n];

    __auto_type multiHandle = curl_multi_init();

    for (int i = 0; i < n; i++)
    {
        wstreams[i] = open_memstream(&fptrs[i], &fsizes[i]);

        handles[i] = curl_easy_init();
        char url[80];
        sprintf(url, "https://jsonplaceholder.typicode.com/users/%i/posts", userIds[i]);

        curl_easy_setopt(handles[i], CURLOPT_URL, url);
        curl_easy_setopt(handles[i], CURLOPT_WRITEDATA, wstreams[i]);
        curl_multi_add_handle(multiHandle, handles[i]);
    }

    int stillRunning;
    do
    {
        CURLMcode mc;
        int numFds;
        mc = curl_multi_perform(multiHandle, &stillRunning);
        if (mc == CURLM_OK && stillRunning)
        {
            mc = curl_multi_poll(multiHandle, NULL, 0, 1000, &numFds);
        }
        if (mc != CURLM_OK)
        {
            stillRunning = 0;
        }
    } while (stillRunning);

    __auto_type posts = json_array();

    for (int i = 0; i < n; i++)
    {
        curl_easy_cleanup(handles[i]);
        fclose(wstreams[i]);
        json_array_append_new(posts, json_loadb(fptrs[i], fsizes[i], 0, NULL));
    }

    curl_multi_cleanup(multiHandle);

    return posts;
}

struct json_t *fetchUsersAlbums(int userIds[], size_t n)
{
    CURL *handles[n];
    char *fptrs[n];
    size_t fsizes[n];
    FILE *wstreams[n];

    __auto_type multiHandle = curl_multi_init();

    for (int i = 0; i < n; i++)
    {
        wstreams[i] = open_memstream(&fptrs[i], &fsizes[i]);

        handles[i] = curl_easy_init();
        char url[80];
        sprintf(url, "https://jsonplaceholder.typicode.com/users/%i/albums", userIds[i]);

        curl_easy_setopt(handles[i], CURLOPT_URL, url);
        curl_easy_setopt(handles[i], CURLOPT_WRITEDATA, wstreams[i]);
        curl_multi_add_handle(multiHandle, handles[i]);
    }

    int stillRunning;
    do
    {
        CURLMcode mc;
        int numFds;
        mc = curl_multi_perform(multiHandle, &stillRunning);
        if (mc == CURLM_OK && stillRunning)
        {
            mc = curl_multi_poll(multiHandle, NULL, 0, 1000, &numFds);
        }
        if (mc != CURLM_OK)
        {
            stillRunning = 0;
        }
    } while (stillRunning);

    __auto_type albums = json_array();

    for (int i = 0; i < n; i++)
    {
        curl_easy_cleanup(handles[i]);
        fclose(wstreams[i]);
        json_array_append_new(albums, json_loadb(fptrs[i], fsizes[i], 0, NULL));
    }

    curl_multi_cleanup(multiHandle);

    return albums;
}

struct json_t *fetchUsersTodos(int userIds[], size_t n)
{
    CURL *handles[n];
    char *fptrs[n];
    size_t fsizes[n];
    FILE *wstreams[n];

    __auto_type multiHandle = curl_multi_init();

    for (int i = 0; i < n; i++)
    {
        wstreams[i] = open_memstream(&fptrs[i], &fsizes[i]);

        handles[i] = curl_easy_init();
        char url[80];
        sprintf(url, "https://jsonplaceholder.typicode.com/users/%i/todos", userIds[i]);

        curl_easy_setopt(handles[i], CURLOPT_URL, url);
        curl_easy_setopt(handles[i], CURLOPT_WRITEDATA, wstreams[i]);
        curl_multi_add_handle(multiHandle, handles[i]);
    }

    int stillRunning;
    do
    {
        CURLMcode mc;
        int numFds;
        mc = curl_multi_perform(multiHandle, &stillRunning);
        if (mc == CURLM_OK && stillRunning)
        {
            mc = curl_multi_poll(multiHandle, NULL, 0, 1000, &numFds);
        }
        if (mc != CURLM_OK)
        {
            stillRunning = 0;
        }
    } while (stillRunning);

    __auto_type todos = json_array();

    for (int i = 0; i < n; i++)
    {
        curl_easy_cleanup(handles[i]);
        fclose(wstreams[i]);
        json_array_append_new(todos, json_loadb(fptrs[i], fsizes[i], 0, NULL));
    }

    curl_multi_cleanup(multiHandle);

    return todos;
}

struct json_t *fetchPostsComments(int *postIds[], size_t nUsers, size_t nPosts[])
{
    int n = 0;
    int offsets[nUsers];
    for (int i = 0; i < nUsers; i++)
    {
        offsets[i] = n;
        n += nPosts[i];
    }

    CURL *handles[n];
    char *fptrs[n];
    size_t fsizes[n];
    FILE *wstreams[n];

    __auto_type multiHandle = curl_multi_init();

    for (int i = 0; i < nUsers; i++)
    {
        for (int j = 0; j < nPosts[i]; j++)
        {
            int k = offsets[i] + j;

            wstreams[k] = open_memstream(&fptrs[k], &fsizes[k]);

            handles[k] = curl_easy_init();
            char url[80];
            sprintf(url, "https://jsonplaceholder.typicode.com/posts/%i/comments", postIds[i][j]);

            curl_easy_setopt(handles[k], CURLOPT_URL, url);
            curl_easy_setopt(handles[k], CURLOPT_WRITEDATA, wstreams[k]);
            curl_multi_add_handle(multiHandle, handles[k]);
        }
    }

    int stillRunning;
    do
    {
        CURLMcode mc;
        int numFds;
        mc = curl_multi_perform(multiHandle, &stillRunning);
        if (mc == CURLM_OK && stillRunning)
        {
            mc = curl_multi_poll(multiHandle, NULL, 0, 1000, &numFds);
        }
        if (mc != CURLM_OK)
        {
            stillRunning = 0;
        }
    } while (stillRunning);

    __auto_type posts = json_array();

    for (int i = 0; i < nUsers; i++)
    {
        __auto_type comments = json_array();
        json_array_append_new(posts, comments);

        for (int j = 0; j < nPosts[i]; j++)
        {
            int k = offsets[i] + j;

            curl_easy_cleanup(handles[k]);
            fclose(wstreams[k]);

            json_array_append_new(comments, json_loadb(fptrs[k], fsizes[k], 0, NULL));
        }
    }

    curl_multi_cleanup(multiHandle);

    return posts;
}

struct json_t *fetchAlbumsPhotos(int *albumIds[], size_t nUsers, size_t nAlbums[])
{
    int n = 0;
    int offsets[nUsers];
    for (int i = 0; i < nUsers; i++)
    {
        offsets[i] = n;
        n += nAlbums[i];
    }

    CURL *handles[n];
    char *fptrs[n];
    size_t fsizes[n];
    FILE *wstreams[n];

    __auto_type multiHandle = curl_multi_init();

    for (int i = 0; i < nUsers; i++)
    {
        for (int j = 0; j < nAlbums[i]; j++)
        {
            int k = offsets[i] + j;

            wstreams[k] = open_memstream(&fptrs[k], &fsizes[k]);

            handles[k] = curl_easy_init();
            char url[80];
            sprintf(url, "https://jsonplaceholder.typicode.com/albums/%i/photos", albumIds[i][j]);

            curl_easy_setopt(handles[k], CURLOPT_URL, url);
            curl_easy_setopt(handles[k], CURLOPT_WRITEDATA, wstreams[k]);
            curl_multi_add_handle(multiHandle, handles[k]);
        }
    }

    int stillRunning;
    do
    {
        CURLMcode mc;
        int numFds;
        mc = curl_multi_perform(multiHandle, &stillRunning);
        if (mc == CURLM_OK && stillRunning)
        {
            mc = curl_multi_poll(multiHandle, NULL, 0, 1000, &numFds);
        }
        if (mc != CURLM_OK)
        {
            stillRunning = 0;
        }
    } while (stillRunning);

    __auto_type albums = json_array();

    for (int i = 0; i < nUsers; i++)
    {
        __auto_type photos = json_array();
        json_array_append_new(albums, photos);

        for (int j = 0; j < nAlbums[i]; j++)
        {
            int k = offsets[i] + j;

            curl_easy_cleanup(handles[k]);
            fclose(wstreams[k]);

            json_array_append_new(photos, json_loadb(fptrs[k], fsizes[k], 0, NULL));
        }
    }

    curl_multi_cleanup(multiHandle);

    return albums;
}
