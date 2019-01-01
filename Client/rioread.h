#ifndef _RIOREAD_H_
#define _RIOREAD_H_

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"sys/types.h"
#include<errno.h>
#include<string.h>

/*robust 的IO函数*/
#define RIO_BUFFER_SIZE 8192
typedef struct{
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFFER_SIZE];
} rio_t;
void rio_init(rio_t*rp,int fd);
/*static ssize_t rio_read(rio_t* rp,void* usrbuf,size_t n);*/
ssize_t rio_readnb(rio_t*rp,void *usrbuf,size_t n);
ssize_t rio_readlineb(rio_t*rp,void *usrbuf,size_t maxlen);
ssize_t rio_writen(int fd ,void*usrbuf,size_t n);
#endif
