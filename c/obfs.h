/*
 * obfs.h - Define shadowsocksR server's buffers and callbacks
 *
 * Copyright (C) 2015 - 2016, Break Wa11 <mmgac001@gmail.com>
 */

#ifndef _OBFS_OBFS_H
#define _OBFS_OBFS_H

#include <stdint.h>
#include <unistd.h>

#define OBFS_HMAC_SHA1_LEN 10

typedef struct server_info {
    char host[256];
    uint16_t port;
    char *param;
    void *g_data;
    uint8_t *iv;
    size_t iv_len;
    uint8_t *recv_iv;
    size_t recv_iv_len;
    uint8_t *key;
    size_t key_len;
    int head_len;
    size_t tcp_mss;
    size_t buffer_size;
}server_info;

typedef struct obfs_struct {
    server_info server;
    void *l_data;
}obfs;

typedef struct obfs_class {
    void * (*init_data)();
    obfs * (*new_obfs)();
    void (*get_server_info)(obfs *self, server_info *server);
    void (*set_server_info)(obfs *self, server_info *server);
    void (*dispose)(obfs *self);

    int (*client_pre_encrypt)(obfs *self,
            char **pplaindata,
            int datalength,
            size_t* capacity);
    int (*client_encode)(obfs *self,
            char **pencryptdata,
            int datalength,
            size_t* capacity);
    int (*client_decode)(obfs *self,
            char **pencryptdata,
            int datalength,
            size_t* capacity,
            int *needsendback);
    int (*client_post_decrypt)(obfs *self,
            char **pplaindata,
            int datalength,
            size_t* capacity);
    int (*client_udp_pre_encrypt)(obfs *self,
            char **pplaindata,
            int datalength,
            size_t* capacity);
    int (*client_udp_post_decrypt)(obfs *self,
            char **pplaindata,
            int datalength,
            size_t* capacity);
}obfs_class;

obfs_class * new_obfs_class(char *plugin_name);
void free_obfs_class(obfs_class *plugin);

void set_server_info(obfs *self, server_info *server);
void get_server_info(obfs *self, server_info *server);
obfs * new_obfs();
void dispose_obfs(obfs *self);

#endif // _OBFS_OBFS_H
