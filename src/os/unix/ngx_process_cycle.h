
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_PROCESS_CYCLE_H_INCLUDED_
#define _NGX_PROCESS_CYCLE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


#define NGX_CMD_OPEN_CHANNEL   1
#define NGX_CMD_CLOSE_CHANNEL  2
#define NGX_CMD_QUIT           3
#define NGX_CMD_TERMINATE      4
#define NGX_CMD_REOPEN         5


#define NGX_PROCESS_SINGLE     0//只有在nginx.conf配置文件中设置为master_process off，且ngx_process值为0时，才有可能会进入单进程工作模式。
#define NGX_PROCESS_MASTER     1//用于指示当前nginx工作方式为master-worker，并且当前进程为master进程
#define NGX_PROCESS_SIGNALLER  2//我们可以通过运行nginx -s reload命令的方式来向正在运行的nginx进程发送信号。这种情况下，其实我们只是想发送一个信号，而并不是真正想要运行一个nginx服务器程序。因此这里我们用NGX_PROCESS_SIGNALLER来表明当前运行的nginx只是一个发送信号的进程。
#define NGX_PROCESS_WORKER     3//表明当前进程是worker进程
#define NGX_PROCESS_HELPER     4//表明当前进程为辅助进程。例如缓存管理器是作为一个辅助进程。


typedef struct {
    ngx_event_handler_pt       handler;
    char                      *name;
    ngx_msec_t                 delay;
} ngx_cache_manager_ctx_t;


void ngx_master_process_cycle(ngx_cycle_t *cycle);
void ngx_single_process_cycle(ngx_cycle_t *cycle);


extern ngx_uint_t      ngx_process;
extern ngx_uint_t      ngx_worker;
extern ngx_pid_t       ngx_pid;
extern ngx_pid_t       ngx_new_binary;
extern ngx_uint_t      ngx_inherited;
extern ngx_uint_t      ngx_daemonized;
extern ngx_uint_t      ngx_exiting;

extern sig_atomic_t    ngx_reap;
extern sig_atomic_t    ngx_sigio;
extern sig_atomic_t    ngx_sigalrm;
extern sig_atomic_t    ngx_quit;
extern sig_atomic_t    ngx_debug_quit;
extern sig_atomic_t    ngx_terminate;
extern sig_atomic_t    ngx_noaccept;
extern sig_atomic_t    ngx_reconfigure;
extern sig_atomic_t    ngx_reopen;
extern sig_atomic_t    ngx_change_binary;


#endif /* _NGX_PROCESS_CYCLE_H_INCLUDED_ */
