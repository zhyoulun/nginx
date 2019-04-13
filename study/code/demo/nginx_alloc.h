//
// Created by lxa on 2019-04-13.
//

#include <zconf.h>
#include <stdlib.h>

#ifndef DEMO_NGINX_ALLOC_H
#define DEMO_NGINX_ALLOC_H

#define ngx_free free

void *ngx_memalign(size_t alignment, size_t size);

#endif //DEMO_NGINX_ALLOC_H
