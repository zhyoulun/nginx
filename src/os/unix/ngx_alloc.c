
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_uint_t  ngx_pagesize;
ngx_uint_t  ngx_pagesize_shift;
ngx_uint_t  ngx_cacheline_size;


//申请一块大小为size的内存，如果成功返回内存首地址，否则返回NULL
void *
ngx_alloc(size_t size, ngx_log_t *log)
{
    void  *p;

    /*
    malloc函数
    Allocates size bytes of uninitialized storage.
    If allocation succeeds, returns a pointer to the lowest (first) byte in the allocated memory block that is suitably aligned for any object type with fundamental alignment.
    */
    p = malloc(size);
    if (p == NULL) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "malloc(%uz) failed", size);
    }

    ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, log, 0, "malloc: %p:%uz", p, size);

    return p;
}

//申请一块大小为size的内存，如果成功返回内存首地址，否则返回NULL，并将内存中每个位置的值设置为0
void *
ngx_calloc(size_t size, ngx_log_t *log)
{
    void  *p;

    p = ngx_alloc(size, log);

    if (p) {
        ngx_memzero(p, size);
    }

    return p;
}


#if (NGX_HAVE_POSIX_MEMALIGN)

//申请一块对齐的内存，大小为size，内存的地址是alignment整数倍，alignment必须是2^N，且必须是sizeof(void *)的倍数
void *
ngx_memalign(size_t alignment, size_t size, ngx_log_t *log)
{
    void  *p;
    int    err;

    /*
    int posix_memalign(void **memptr, size_t alignment, size_t size);
    The function posix_memalign() allocates size bytes and places the
       address of the allocated memory in *memptr.  The address of the
       allocated memory will be a multiple of alignment, which must be a
       power of two and a multiple of sizeof(void *).  If size is 0, then
       the value placed in *memptr is either NULL, or a unique pointer value
       that can later be successfully passed to free(3).
    */
    err = posix_memalign(&p, alignment, size);

    if (err) {
        ngx_log_error(NGX_LOG_EMERG, log, err,
                      "posix_memalign(%uz, %uz) failed", alignment, size);
        p = NULL;
    }

    ngx_log_debug3(NGX_LOG_DEBUG_ALLOC, log, 0,
                   "posix_memalign: %p:%uz @%uz", p, size, alignment);

    return p;
}

#elif (NGX_HAVE_MEMALIGN)

void *
ngx_memalign(size_t alignment, size_t size, ngx_log_t *log)
{
    void  *p;

    /*
    void *memalign(size_t alignment, size_t size);
    The obsolete（废弃） function memalign() allocates size bytes and returns a
       pointer to the allocated memory.  The memory address will be a
       multiple of alignment, which must be a power of two.
    */
    p = memalign(alignment, size);
    if (p == NULL) {
        ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,
                      "memalign(%uz, %uz) failed", alignment, size);
    }

    ngx_log_debug3(NGX_LOG_DEBUG_ALLOC, log, 0,
                   "memalign: %p:%uz @%uz", p, size, alignment);

    return p;
}

#endif
