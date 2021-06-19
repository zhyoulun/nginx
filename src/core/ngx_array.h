
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    void        *elts;//指向实际的数据存储区域。
    ngx_uint_t   nelts;//数组实际元素个数。
    size_t       size;//数组单个元素的大小，单位是字节。
    ngx_uint_t   nalloc;//数组的容量。表示该数组在不引发扩容的前提下，可以最多存储的元素的个数。当nelts增长到达nalloc 时，如果再往此数组中存储元素，则会引发数组的扩容。数组的容量将会扩展到原有容量的2倍大小。实际上是分配新的一块内存，新的一块内存的大小是原有内存大小的2倍。原有的数据会被拷贝到新的一块内存中。
    ngx_pool_t  *pool;//该数组用来分配内存的内存池。
} ngx_array_t;


//创建一个空的ngx_array_t
ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
//销毁该数组对象，并释放其分配的内存回内存池。
void ngx_array_destroy(ngx_array_t *a);
//在数组a上新追加一个元素，并返回指向新元素的指针。需要把返回的指针使用类型转换，转换为具体的类型，然后再给新元素本身或者是各字段（如果数组的元素是复杂类型）赋值。
void *ngx_array_push(ngx_array_t *a);
//在数组a上追加n个元素，并返回指向这些追加元素的首个元素的位置的指针。
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);


//初始化ngx_array_t
static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
