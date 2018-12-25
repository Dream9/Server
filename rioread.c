#include"csapp.h"
#include"macro.h"
//主要实现了一个稳健的read函数（带有buffer)
//

//rio_t结构体
//为了简单，定义在了caspp.h
//#define RIO_BUFFER_SIZE 8192
//
//typedef struct {
//    int rio_fd;  //文件描述符
//    int rio_cnt; //缓冲未读取长度
//    char *rio_bufptr;  //未读取缓冲区指针
//    char rio_buf[RIO_BUFFER_SIZE];  //缓冲区
//} rio_t;

//文件描述符与rio缓冲区关联
/*这里应该叫做rio_readinit更合适*/
void rio_init(rio_t*rp,int fd){
    rp->rio_fd=fd;
    rp->rio_cnt=0;
    rp->rio_bufptr=rp->rio_buf;
}

static ssize_t rio_read(rio_t*rp,void *usrbuf,size_t n){
    int cnt;
    while(rp->rio_cnt<=0){
        //装填缓冲区
        rp->rio_cnt=read(rp->rio_fd,rp->rio_buf,sizeof(rp->rio_buf));
        if(rp->rio_cnt<0){
            if(errno!=EINTR) /*Interrupted by sig handler return*/
                return -1;
            //其他情况下，重现陷入内核read
        }
        else if(rp->rio_cnt==0)
            return 0;  /*EOF*/
        else
            rp->rio_bufptr=rp->rio_buf;
    }
    cnt=rp->rio_cnt<n?rp->rio_cnt:n;
    memcpy(usrbuf,rp->rio_bufptr,cnt);
    rp->rio_cnt-=cnt;
    rp->rio_bufptr+=cnt;
    return cnt;
}

ssize_t rio_readnb(rio_t*rp,void *usrbuf,size_t n){
    size_t nleft=n;
    ssize_t nread;
    char*bufp=usrbuf;

    while(nleft>0){
        if((nread=rio_read(rp,bufp,nleft)<0))
            return -1;   //errno set by read()
        else if(nread==0)
            break;  /*EOF*/
        nleft-=nread;
        bufp+=nread;
    }
    return (n-nleft);
}

ssize_t rio_readlineb(rio_t*rp,void *usrbuf,size_t maxlen){
    int n,rc;
    char c,*bufp=usrbuf;
    for(n=1;n<maxlen;n++){
        if((rc=rio_read(rp,&c,1))==1)
        {
            *bufp++=c;
            if(c=='\n'){
                ++n;
                break;
            }
        }else if(rc==0){
            if(n==1)
                return 0;
            else
                break;
        }else
            return -1;
    }
    *bufp='\0';
    return n-1;
}

//无缓冲的write
ssize_t rio_writen(int fd ,void*usrbuf,size_t n){
    size_t nleft=n;
    ssize_t nwritten;
    char *bufp=usrbuf;

    while(nleft>0){
        if((nwritten=write(fd,bufp,nleft))<=0){
            if(errno==EINTR)
                nwritten=0;
            else 
                return -1;
        }
        nleft-=nwritten;
        bufp+=nwritten;
    }
    return n;
}
