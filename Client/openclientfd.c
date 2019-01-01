
//套接字接口的辅助函数
//通过函数封装，使得它是可重入的、与协议无关的

//流程：
//getaddrinfo--->socket---->connect
//
//#include<sys/types.h>
//#include<sys/socket.h>

#include"openclientfd.h"

int open_clientfd(char * hostname,char *port){
    //
    int clientfd;
    int err_num;
    struct addrinfo hints,*listp,*p;

    //get a list of potential server address
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_socktype=SOCK_STREAM;/*类型是建立连接*/
    hints.ai_flags=AI_ADDRCONFIG;/*推荐配置，依据本机配置在IPV4或6返回*/
    hints.ai_flags|=AI_NUMERICSERV;
    err_num=(getaddrinfo(hostname,port,&hints,&listp));
    if(err_num!=0){
        fprintf(stderr,"Something Brokendown(getaddrinfo)[%s:%s:%d]:%s",
                __FILE__,__func__,__LINE__,gai_strerror(err_num));
        exit(EXIT_FAILURE);
    }
    printf("尝试建立连接");

    //遍历连接
    for(p=listp;p;p=p->ai_next){
        if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
            continue;//Socket failed

        if(connect(clientfd,p->ai_addr,p->ai_addrlen)!=-1)
            break;//success
        IF_CODE(close(clientfd));//关闭无用的描述符
    }

    //IF_CODE(freeaddrinfo(listp));
    // 注意freeaddrinfo 没有返回值
    freeaddrinfo(listp);
    if(!p)
        return -1;
    else
        return clientfd;


}
