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
/**    �ṩ���񷽽ӿ�
   �˺�������ǰ���������ص�zk��Ⱥά�������ݽṹ�ϣ�����B���ܿ�����ǰ�������ṩ����Ķ˿ڡ�
   �˺���Ϊ�첽������ֻ�����κεط����ü��ɣ���Ӱ����������ҵ�����̡������Զ�������zk��Ⱥ��������
   ����˵����
zk_host_ports:zk��Ⱥ���б���ʽ�硱127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183��
path:���ص�·�������硱/cluster��,�����ṩ��ͬ����Ļ��������ص���·���£����ɼ�Ⱥ��
local_host_port:�������ṩ�����ip�Ͷ˿�
*/
zhandle_t* register_to_zk(const char* zk_host_ports, const char* path, const char* local_host_port ) ;

/**********************ʹ�÷��񷽽ӿ�****************/
/*
   �ڻ�ü�Ⱥ�Ļ���ǰ,��Ҫ���ȵ��ô˺���������zk��Ⱥ�����ṩ����A���м�ء�
Host_ports: ��Ⱥ���б���ʽ�硱127.0.0.1:2181,127.0.0.1:2182,127.0.0.1:2183
cluster_node: �ṩ���񷽵Ĺ���·��
*/

zhandle_t* monitor_by_zk(const char *host_ports, const char *cluster_node);

/*
   ��ü�Ⱥ�е�ĳһ̨���õĻ������ɹ�����0��ʧ�ܷ���-1
Host_port: ���ڷ��ؿ��õĻ��������ڴ���Ҫ�����߷��䣬�ڲ��Ѿ�ʵ���˸��ؾ��⡣���ص�ַ��ʽΪ��127.0.0.1:2181��
N: host_port�ڴ��С
*/

int get_server_in_zk(char *host_port, int n);

#endif

#endif