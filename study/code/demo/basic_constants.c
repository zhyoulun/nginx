//
// Created by lxa on 2019-04-13.
//

#include <zconf.h>
#include "basic_constant.h"

void basic_constant_init() {
    ngx_pagesize = getpagesize();
}