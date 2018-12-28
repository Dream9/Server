#include"client.h"
#include"rioread.h"
#include"macro.h"
#include"openclientfd.h"

/*
 * 客户端测试
 */

int main(int argc,char*argv[]){
    char buf[_BUF_LEN];
    int sfd;
    int len;
    char *host,*port;
    rio_t rio_buf;

    if(argc!=3){
        fprintf(stderr,"usage:%s<host><port>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    host=argv[1];
    port=argv[2];

    sfd=open_clientfd(host,port);
    rio_init(&rio_buf,sfd);

    /*生成简单的请求*/
    strcpy(buf,_STR_HEAD_1);
    strcat(buf,host);
    strcat(buf,_STR_HEAD_2);
    rio_writen(sfd,buf,strlen(buf));
    /*获得反馈内容*/
    while(len=(rio_readnb(&rio_buf,buf,sizeof buf-1))>0){
        buf[len]='\0';
        printf("%s",buf);
    }
    putchar('\n');
    close(sfd);
    return 0;

}
