#ifndef ZOOKEEPER_CLUSTER_H
#define ZOOKEEPER_CLUSTER_H

#include "zookeeper.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#ifdef __cplusplus

extern "C" zhandle_t* register_to_zk(const char* zk_host_ports, const char* path, const char* local_host_port ) ;
extern "C" zhandle_t* monitor_by_zk(const char *host_ports, const char *cluster_node);
extern "C" int get_server_in_zk(char *host_port, int n);
#else
/**    提供服务方接口
   此函数将当前服务器挂载到zk集群维护的数据结构上，这样B就能看到当前机器及提供服务的端口。
   此函数为异步函数，只需在任何地方调用即可，不影响其他正常业务流程。它会自动保持与zk集群的心跳。
   参数说明：
zk_host_ports:zk集群的列表，格式如”127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183”
path:挂载的路径，比如”/cluster”,所有提供相同服务的机器都挂载到该路径下，构成集群。
local_host_port:本机器提供服务的ip和端口
*/
zhandle_t* register_to_zk(const char* zk_host_ports, const char* path, const char* local_host_port ) ;

/**********************使用服务方接口****************/
/*
   在获得集群的机器前,需要首先调用此函数，连接zk集群，对提供服务方A进行监控。
Host_ports: 集群的列表，格式如”127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183
cluster_node: 提供服务方的挂载路径
*/

zhandle_t* monitor_by_zk(const char *host_ports, const char *cluster_node);

/*
   获得集群中的某一台可用的机器，成功返回0，失败返回-1
Host_port: 用于返回可用的机器，该内存需要调用者分配，内部已经实现了负载均衡。返回地址格式为”127.0.0.1:2181”
N: host_port内存大小
*/

int get_server_in_zk(char *host_port, int n);

#endif

#endif