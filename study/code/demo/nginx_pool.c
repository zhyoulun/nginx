//
// Created by lxa on 2019-04-13.
//

#include "nginx_pool.h"
#include "basic_constant.h"
#include "nginx_alloc.h"


ngx_pool_t *ngx_create_pool(size_t size) {
    ngx_pool_t *p;

    p = ngx_memalign(NGX_POOL_ALIGNMENT, size);
    if (p == NULL) {
        return NULL;
    }

    p->d.last = (u_char *) p + sizeof(ngx_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_t);
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    return p;
}

void ngx_destroy_pool(ngx_pool_t *pool) {
    ngx_pool_t *p;
    ngx_pool_t *n;
    for (p = pool, n = p->d.next;; p = n, n = n->d.next) {
        ngx_free(p);
        if (n == NULL) {
            break;
        }
    }
}