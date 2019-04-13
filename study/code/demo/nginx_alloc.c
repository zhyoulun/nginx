//
// Created by lxa on 2019-04-13.
//

#include <mm_malloc.h>
#include "nginx_alloc.h"

void *ngx_memalign(size_t alignment, size_t size) {
    int err;
    void *p;
    err = posix_memalign(&p, alignment, size);
    if (err) {
        p = NULL;
    }
    return p;
}