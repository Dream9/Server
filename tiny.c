#include "csapp.h"

void doit(int fd);  //服务器响应 
void read_requesthdrs(rio_t *rp);
int parse_uri(char * uri,char *filename,char *cgiargs);  //解析uri
void get_filetype(char *filename,char *filetype);
void serve_static (int fd,char *filename,int filesize);  //静态服务
void serve_dynamic(int fd,char *filename,cahr *cgiargs);  //动态服务
void clienterror(int fd,char *cause,char *errnum,
        char *shortmsg,char *longmsg);    //错误信息
int main(int argc,char **argv){
    int listenfd,connfd;//监听描述符、已连接描述符
    char hostname[MAXLINE],port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    //检查command line args
    if(argc!=2){
        fprintf(stderr,"usage:%s <port>\n",argv[0]);
        exit(1);
    }

    listenfd=Open_listenfd(argv[1]);
    while(1){
        clientlen=sizeof(clientaddf);
        connfd=Accept(listenfd,(SA*)&clientaddr,&clientlen);
        Getnameinfo((SA*) &clientaddr,clientlen,hostname,MAXLINE,
                port,MAXLINE,0);
        printf("Accepted connection from (%s,%s)\n",hostname,port);
        doit(connfd);
        close(connfd);
    }
}

    
