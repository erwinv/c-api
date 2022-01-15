#pragma once
#include <jansson.h>

void init();
void cleanup();

struct json_t *fetchUsers();

struct json_t *fetchUsersPosts(int userIds[], size_t n);
struct json_t *fetchUsersAlbums(int userIds[], size_t n);
struct json_t *fetchUsersTodos(int userIds[], size_t n);

struct json_t *fetchPostsComments(int *postIds[], size_t nUsers, size_t nPosts[]);
struct json_t *fetchAlbumsPhotos(int *albumIds[], size_t nUsers, size_t nAlbums[]);
