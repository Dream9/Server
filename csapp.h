#ifndef CSAPP_H
#define CSAPP_H
#endif

#include<stdlib.h>
#include<stdio.h>
//跟踪错误记录
#include<errno.h>
//建立套接字描述符
#include<sys/socket.h>
#include<netdb.h>
//回收僵尸进程
#include<sys/wait.h>
//设置信号事件
#include<sys/signal.h>
//Linux内置类型信息
#include<sys/types.h>
//Unix标准库
#include<unistd.h>
//系统状态
#include<sys/stat.h>
//sockaddr_in结构
#include<arpa/inet.h>
#include<netinet/in.h>

#include<pthread.h>
#include<string.h>

//
//调试信息设置
#ifdef _DEBUG

    #ifdef DEBUG_TO_FILE
        #define DEBUG_FILE "./debugmsg"
        //调试信息输出到文件
        #define DEBUG_BUFFER_MAX 4096
        #define DebugMsg(fmt, ...) {\
            char buffer[DEBUG_BUFFER_MAX]={0};\
            snprintf(buffer,DEBUG_BUFFER_MAX,\
                    "[%s:%d]fmt",__FUNCTION__,__LINE__,##__VA__ARGS__);\
            FILE* fd=fopen(DEBUG_FILE,"a");\
            if(fd!=NULL){\
                fwrite(buffer,strlen(buffer),1,fd);\
                fflush(fd);\
                fclose(fd);\
            }\
        }
        
    #else
    //调试信息输出到终端
        #define DebugMsg(fmt, ...) \
            fprintf(stderr,"[%s:%s:%d]"fmt,__FILE__,__FUNCTION__, \
                    __LINE__,##__VA_ARGS__);
    #endif
#else
    //错误封装函数
    #define IF_CODE(return_code) \
       if(return_code<0){\
           DebugMsg(return_code);exit(EXIT_FAILURE);\
       }
    
    //发行版本，什么也不做
    #define DebugMsg(fmt)  
#endif

//辅助变量与宏
//
//char 缓冲区大小
#define _INT_BUF (1024)
//listen监听队列大小
#define _INT_LIS (7)

//RIO函数   /*已经废弃*/
//ssize_t getfdline(size_t fd,char*buf,size_t sz);

//返回400请求解析失败，客户端代码错误
extern void response_400(int cfd);
//返回404请求文件未找到错误
extern void response_404(int cfd);
//返回501服务器不支持的请求
extern void response_501(int cfd);
//返回500服务器内部错误
extern  void response_500(int cfd);
//返回200请求成功
extern void response_200(int cfd);


//发送文件到客户端
void response_file(int cfd,const char *path);


//带改进
/////
//启动服务器的监听句柄   弃用
//int serve_start(uint16_t * pport);

//多线程处理例程
void* response_echo(void*arg);


//处理函数
void response_cgi(int cfd,const char*path,
        const char*type,const char*query);

//与协议无关的可重入的套接字建立函数
extern int open_listenfd(char*port);
extern int open_clientfd(char*hostname,char*port);
//
typedef struct{
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[_INT_BUF];
}rio_t;
//RIO的读写函数
extern ssize_t rio_readlineb(rio_t *rp,void*usrbuf,size_t maxlen);
extern ssize_t rio_readnb(rio_t *rp,void*usrbuf,size_t n);
extern ssize_t rio_writen(int fd,void*usrbuf,size_t n);

//#线程处理例程   弃用
//void*request_accept(void *arg);

