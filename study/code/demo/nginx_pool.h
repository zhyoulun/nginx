//
// Created by lxa on 2019-04-13.
//

#ifndef DEMO_NGINX_POOL_H
#define DEMO_NGINX_POOL_H

#include <zconf.h>
#include "basic_type.h"

typedef struct ngx_pool_s ngx_pool_t;

typedef struct {
    u_char *last;
    u_char *end;
    ngx_pool_t *next;
    ngx_uint_t failed;
} ngx_pool_data_t;


struct ngx_pool_s {
    ngx_pool_data_t d;
    size_t max;
    ngx_pool_t *current;
};

ngx_pool_t *ngx_create_pool(size_t size);

void ngx_destroy_pool(ngx_pool_t *pool);

void *ngx_palloc(ngx_pool_t *pool, size_t size);

#endif //DEMO_NGINX_POOL_H
