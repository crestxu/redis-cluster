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

zhandle_t* register_to_zk(const char* zk_host_ports, const char* path, const char* local_host_port ) ;
zhandle_t* monitor_by_zk(const char *host_ports, const char *cluster_node);
int get_server_in_zk(char *host_port, int n);

#endif

#endif