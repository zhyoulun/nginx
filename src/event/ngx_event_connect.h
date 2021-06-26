
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_EVENT_CONNECT_H_INCLUDED_
#define _NGX_EVENT_CONNECT_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


#define NGX_PEER_KEEPALIVE           1
#define NGX_PEER_NEXT                2
#define NGX_PEER_FAILED              4


typedef struct ngx_peer_connection_s  ngx_peer_connection_t;

//通过该方法由连接池中获取一个新连接
typedef ngx_int_t (*ngx_event_get_peer_pt)(ngx_peer_connection_t *pc,
    void *data);
//通过该方法将使用完毕的连接释放给连接池
typedef void (*ngx_event_free_peer_pt)(ngx_peer_connection_t *pc, void *data,
    ngx_uint_t state);
typedef void (*ngx_event_notify_peer_pt)(ngx_peer_connection_t *pc,
    void *data, ngx_uint_t type);
typedef ngx_int_t (*ngx_event_set_peer_session_pt)(ngx_peer_connection_t *pc,
    void *data);
typedef void (*ngx_event_save_peer_session_pt)(ngx_peer_connection_t *pc,
    void *data);


//Nginx定义了基本的数据结构ngx_connection_t来表示连接。由客户端主动发起、Nginx服务器被动接收的TCP连接，这类可以称为被动连接。还有一类连接，在某些请求的处理过程中，Nginx会试图主动向其他上游服务器建立连接，并以此连接与上游服务器通信，Nginx定义ngx_peer_connection_t结构来表示，这类可以称为主动连接。本质上来说，主动连接是以ngx_connection_t结构体为基础实现的。
struct ngx_peer_connection_s {
    ngx_connection_t                *connection;

    struct sockaddr                 *sockaddr;//远端服务器socket信息
    socklen_t                        socklen;
    ngx_str_t                       *name;

    ngx_uint_t                       tries;//连接失败后可以重试的次数
    ngx_msec_t                       start_time;

    ngx_event_get_peer_pt            get;//从连接池中获取长连接，必须使用该方法
    ngx_event_free_peer_pt           free;
    ngx_event_notify_peer_pt         notify;
    void                            *data;//该data成员作为上面方法的传递参数

#if (NGX_SSL || NGX_COMPAT)
    ngx_event_set_peer_session_pt    set_session;
    ngx_event_save_peer_session_pt   save_session;
#endif

    ngx_addr_t                      *local;//本地地址信息

    int                              type;
    int                              rcvbuf;//接收缓冲区大小

    ngx_log_t                       *log;

    unsigned                         cached:1;//标识该连接已经缓存
    unsigned                         transparent:1;

                                     /* ngx_connection_log_error_e */
    unsigned                         log_error:2;

    NGX_COMPAT_BEGIN(2)
    NGX_COMPAT_END
};


ngx_int_t ngx_event_connect_peer(ngx_peer_connection_t *pc);
ngx_int_t ngx_event_get_peer(ngx_peer_connection_t *pc, void *data);


#endif /* _NGX_EVENT_CONNECT_H_INCLUDED_ */
