#include "zookeeper_cluster.h"
#include <pthread.h>
#define MAX_SERVERS 100 
#define HOST_LENGTH 50
static int is_running = 0 ;
struct Servers_in_zk{
    char host_ports[MAX_SERVERS][HOST_LENGTH];
    int servers_num ;
} ;
//double server_list. to avoid confilict when updating and reading in the same time.
static struct Servers_in_zk server_list[2] ;
static int valid_flag ;//which server_list is the newest.
static pthread_mutex_t zk_mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t zk_mutex2 = PTHREAD_MUTEX_INITIALIZER;

zhandle_t* register_to_zk(const char* zk_host_port, const char* path, const char* local_host_port ) {
    char buffer[512];
    char fullpath[512] ;
    int rc ;
    zoo_set_debug_level(ZOO_LOG_LEVEL_ERROR);
    
    zhandle_t *zh = zookeeper_init(zk_host_port, 0, 10000, 0, 0, 0);
    if (!zh) {
      return NULL;
    }
    
// struct ACL CREATE_ONLY_ACL[] ={ {ZOO_PERM_WRITE,{"digest","user:pwd"}}, 
// {ZOO_PERM_READ,{"ip","127.0.0.1"}}, 
// {ZOO_PERM_CREATE,{"world","anyone"}} };
// struct ACL_vector my_acl_vec = {3, CREATE_ONLY_ACL};
    struct Stat stat ;
    if(ZNONODE == zoo_exists(zh, path, 0, &stat)){
        rc = zoo_create(zh,path,"cluster", strlen("cluster"), &ZOO_OPEN_ACL_UNSAFE, 0, buffer, sizeof(buffer)-1);
        if( rc != ZOK )
            return NULL;
    }
    strcpy(fullpath, path);
    strcat(fullpath, "/");
    strcat(fullpath, local_host_port);
    rc = zoo_create(zh, fullpath, local_host_port, strlen(local_host_port), &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, buffer, sizeof(buffer)-1);
    if(rc != ZOK ){
        printf("zookeeper zoo_create error\n");
        exit(rc);
    }
    return zh;
}


void deal_strvec(const struct String_vector *strings) {
    pthread_mutex_lock(&zk_mutex1);
    int i;
    int to_update = (valid_flag+1) % 2 ;
    if (strings){
        for (i=0; i < strings->count; i++) {
            strcpy(server_list[to_update].host_ports[i], strings->data[i]);
        }
        server_list[to_update].servers_num = i;
        valid_flag = to_update ;
    }
    pthread_mutex_unlock(&zk_mutex1);
}

void watcher1(zhandle_t *zh, int type, int state, const char *path, void* context) {}

void watcher2(zhandle_t *zh, int type, int state, const char *path, void* context) {
    if (!zh) {
        exit(-1) ;
    }
    struct String_vector str_vec ;
    int rc = zoo_wget_children(zh, path, watcher2, 0, &str_vec);
    if(type == 4){//zookeeper集群的变化也会引起watcher2函数的执行，而且我们要监听的是被管理集群的变化
        //zookeeper集群的变化type为-1，被监听集群的节点发生变化，type为-1
        deal_strvec(&str_vec);
    }else if(type == -1){
    }
}

zhandle_t* monitor_by_zk(const char *host_port, const char *cluster_node){
    if(!is_running){
        valid_flag = 1 ;
        server_list[0].servers_num = server_list[1].servers_num =0 ;
        zhandle_t *zh = zookeeper_init( host_port, watcher1, 10000, 0, 0, 0);
        if (!zh) {
            printf("zh cannot connect\n");
            return NULL;
        }
        struct String_vector str_vec ;
        int rc = zoo_wget_children(zh, cluster_node, watcher2, 0, &str_vec);
        deal_strvec(&str_vec);
        is_running = 1 ;
        return zh ;
    }
}
int get_server_in_zk(char *host_port, int n){
    static int cursor = 0;
    if( is_running ){

        pthread_mutex_lock(&zk_mutex2);
        if (server_list[valid_flag].servers_num == 0 ){
            strcpy(host_port, "");
        }
        cursor = (cursor+1) % (server_list[valid_flag].servers_num) ;
        strcpy(host_port,server_list[valid_flag].host_ports[cursor] );
        pthread_mutex_unlock(&zk_mutex2);
        return 0 ;
    }else {
        printf("zookeeper error:get_server_in_zk()\n");
        return -1 ;
    }
}
/*
void thread_fun(void* i){
    char ser[30];
    int *t = (int *)i;
    int count = 10000;
    while(count--){
        
        get_server_in_zk(ser,30);
        printf("thread%d :%s\n", *t,ser);
    }
}
int main(int ac, char **av){
    zhandle_t *zh = monitor_by_zk("127.0.0.1:2181", "/asncluster");
    int count = 10000;
    char server[30] ;
    pthread_t th1 ;
    int thread_no1 = 1;
    pthread_create(&th1, NULL,(void *)thread_fun, (void *)&thread_no1);

    pthread_t th2 ;
    int thread_no2 = 2;
    pthread_create(&th2, NULL,(void *)thread_fun, (void *)&thread_no2);

    while(count--){
      get_server_in_zk(server, 30);
      printf("main:%s\n", server);
    }
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    zookeeper_close(zh);
}

*/

/*
int main(int ac, char **av){
    zhandle_t *zh = register_to_zk("127.0.0.1:2181,127.0.0.1:2182", "/asncluster", "192.168.3.1:123");
    getchar();
    return 0 ;
}
*/