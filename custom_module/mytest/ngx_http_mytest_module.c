#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);

/*
struct ngx_command_s {
    ngx_str_t             name;//配置项名称，例如gzip
    ngx_uint_t            type;//配置项类型，指定配置项可以出现的位置。例如：出现在server{}或者location{}中，以及它可以携带的参数个数
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);//出现了name中指定的配置项后，将会调用set方法处理配置项的参数
    ngx_uint_t            conf;//在配置文件中的偏移量
    ngx_uint_t            offset;//通常用于使用预设的解析方法解析配置项，这是配置模块的一个优秀设计，需要与conf配合使用
    void                 *post;//配置项读取后的处理方法，必须是ngx_conf_post_t结构的指针
};
*/
static ngx_command_t ngx_http_mytest_commands[] = {
    {
        ngx_string("mytest"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
        ngx_http_mytest,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL,
    },
    ngx_null_command,
};

static ngx_http_module_t ngx_http_mytest_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

ngx_module_t ngx_http_mytest_module = {
    NGX_MODULE_V1,
    &ngx_http_mytest_module_ctx,           /* module context */
    ngx_http_mytest_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING,
};


static char *ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_mytest_handler;
    return NGX_CONF_OK;
}


static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r){
    if(!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))){
        return NGX_HTTP_NOT_ALLOWED;
    }
    return NGX_HTTP_OK;
}