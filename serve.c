#include"csapp.h"
#include"macro.h"
int main(int argc,char **argv){
	printf("服务器启动\n");
    if(argc!=2){
        fprintf(stderr,"usage:%s<port>[无效的服务名]\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    pthread_attr_t attr;
    char* port=argv[1];//
    int sfd=open_listenfd(port);
    if(sfd<0){
        printf("未能建立监听端口连接");
        exit(-1);

    }
    printf("ceshi");
    printf("httpd running on service %s.\n",port);
    //初始化线程属性
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    for(;;){
        pthread_t tid;
        struct sockaddr_in caddr;
        socklen_t clen=sizeof(caddr);
        int cfd=accept(sfd,(struct sockaddr*)&caddr,&clen);
        IF_CODE(cfd);
        if(pthread_create(&tid,&attr,response_echo,(void*)cfd)!=0){
            printf("Create Thread Error");
            close(sfd);
            exit(EXIT_FAILURE);
        }
    }
    pthread_attr_destroy(&attr);
    close(sfd);
    return 0;
}
