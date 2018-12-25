#include"csapp.h"
#include"macro.h"
//getaddrinfo-->sock-->bind--->listen---->accept--->ok
//
#define INT_LIS 1024
#include<netdb.h>
int open_listenfd(char*port){
    int lfd,optval=1;
    struct addrinfo hints,*listp,*p;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
    hints.ai_flags|=AI_NUMERICSERV;
    //////////////////////////////////
    if(int err_num=getaddrinfo(NULL,port,&hints,&listp)!=0){
        //失败后，返回非零值，代表错误代码
        fprintf(stderr,"Something Brokendown[%s:%d:%s][%d:]\r\n",
                __FILE__,__LINE__,__func__,err_num);
        exit(EXIT_FAILURE);
    }

    for(p=listp;p;p=p->ai_next){
        if((lfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
            continue;

        IF_CODE(setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,
                    (const void*)&optval,sizeof(int)));

        if(bind(lfd,p->ai_addr,p->ai_addrlen)==0)
            break;/*success*/
        close(lfd);
    }
    //:IF_CODE(freeaddrinfo(listp));
    if(!p)
        return -1;

    if(listen(lfd,INT_LIS)<0){
        close(lfd);
        return -1;
    }
    return lfd;

}
