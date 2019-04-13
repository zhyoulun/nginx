//
// Created by lxa on 2019-04-13.
//

#include "basic_type.h"

#ifndef DEMO_BASIC_CONSTANT_H
#define DEMO_BASIC_CONSTANT_H

#define NGX_POOL_ALIGNMENT 16

ngx_uint_t ngx_pagesize;

#define NGX_MAX_ALLOC_FROM_POOL (ngx_pagesize - 1)

void basic_constant_init();

#endif //DEMO_BASIC_CONSTANT_H
