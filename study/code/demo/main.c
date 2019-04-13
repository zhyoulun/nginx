#include <stdio.h>
#include <zconf.h>
#include "basic_constant.h"

int init() {
    basic_constant_init();
}

int main() {
    init();

    printf("%d\n", NGX_MAX_ALLOC_FROM_POOL);
    printf("Hello, World!\n");

    return 0;
}