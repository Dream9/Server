#include"csapp.h"

int main(int argc,char **argv){
    pthread_attr_t attr;
    char* port;//
    int sfd=open_listenfd(port);
    if(sfd==-1){
        printf("未能建立监听端口连接");
        exit(-1);

    }

    printf("httpd running on port %s.\n",port);
    //初始化线程属性
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    for(;;){
        pthread_t tid;
        struct sockaddr_in caddr;
        socklen_t clen=sizeof(caddr);
        int cfd=accept(sfd,(struct sockaddr*)&caddr,&clen);
        IF_CODE(cfd);
        IF_CODE(pthread_create(&tid,&attr,response_echo,(void*)cfd));
    }
    pthread_attr_destroy(&attr);
    close(sfd);
    return 0;
}
