#include "zookeeper_cluster.h"
#include<pthread.h>

void thread_fun(void* i){
    char ser[30];
    int *t = (int *)i;
    int count = 10000;
    while(1){
        get_server_in_zk(ser,30);
        sleep(300);
        printf("thread%d :%s\n", *t,ser);
    }
}
int main(int ac, char **av){

    if(ac<2) {
        printf("bad arguments\n");
        return -1;
    }
	zhandle_t *zh = register_to_zk("127.0.0.1:2181", "/asncluster", av[1]);
    zhandle_t *zh2= monitor_by_zk("127.0.0.1:2181", "/asncluster");
    int count = 10000;
    char server[30] ;
    pthread_t th1 ;
    int thread_no1 = 1;
    pthread_create(&th1, NULL,(void *)thread_fun, (void *)&thread_no1);


/*    while(count--){
      get_server_in_zk(server, 30);
      printf("main:%s\n", server);
    }*/
    pthread_join(th1,NULL);
while(1);
    zookeeper_close(zh);

}



/*
int main(int ac, char **av){
    zhandle_t *zh = register_to_zk("127.0.0.1:2181,127.0.0.1:2182", "/asncluster", "192.168.3.1:123");
    getchar();
    return 0 ;
}
*/

