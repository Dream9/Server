#include"csapp.h"

//判断是否是空白符
#define isspace(c) \
    ((c==' '||(c>='\t'&&c<='\r')))

//定义了常见的状态函数
//

inline void response_404(int cfd){
    const char* res="HTTP/1.0 404 NOT FOUND\r\n"
        "Server:ceshi simple httpd 1.0/r/n"
        "Content-Type:text/html\r\n"
        "\r\n"
        "<html>"
        "<head><title>界面被查水表了</title></head?"
        "<body><p>404 估计是会不来了</p></body>\r\n"
        "</html>";
    rio_writen(cfd,res,strlen(res));
}
inline void response_400(int cfd){
    const char* res="HTTP/1.0 400 BAD REQUEST\r\n"
        "Server:ceshi simple httpd 1.0/r/n"
        "Content-Type:text/html\r\n"
        "\r\n"
        "<p>请求有问题</p>\r\n";
    rio_writen(cfd,res,strlen(res));
}
inline void response_501(int cfd){
    const char* res="HTTP/1.0 501 METHOD NOT IMPLEMENTED\r\n"
        "Server:ceshi simple httpd 1.0/r/n"
        "Content-Type:text/html\r\n"
        "\r\n"
        "<html>"
        "<head><title>小伙子不要乱请求</title></head>\r\n"
        "<body><p>年轻人总想搞出点大事情</p></body>\r\n"
        "</html>";
    rio_writen(cfd,res,strlen(res));
}
inline void response_500(int cfd){
    const char* res="HTTP/1.0 500 INTERNET SEVER ERROR\r\n"
        "Server:ceshi simple httpd 1.0/r/n"
        "Content-Type:text/html\r\n"
        "\r\n"
        "<html>"
        "<head><title>sorry</title></head>/r/n"
        "<body><p>最近有点方</p></body>\r\n"
        "</html>";
    rio_writen(cfd,res,strlen(res));
}
inline void response_200(int cfd){
    const char* res="HTTP/1.0 200 OK\r\n"
        "Server:ceshi simple httpd 1.0/r/n"
        "Content-Type:text/html\r\n"
        "\r\n";
        
    rio_writen(cfd,res,strlen(res));
}



//定义正常响应操作

//请求文件操作
void response_file(int cfd,const char*path){
    FILE* txt;///////fstream ,,相当于
    char buf[_INT_BUF];

    //读取报文头？？？过滤？？
    //
    //

    if((txt=fopen(path,"r"))==NULL)
        response_404(cfd);
    else{
        response_200(cfd);
        while(fgets(buf,sizeof buf,txt))
            write(cfd,buf,strlen(buf));
    }
    fclose(txt);
}

//多线程处理的函数
//void* 是传进来的描述符，强制转换即可
//
//注意在外层设置detached属性，防止泄漏
void *response_echo(void*arg){
    int fd=(int)arg;
    char buf[_INT_BUF],path[_INT_BUF>>1],type[_INT_BUF>>5];
    //
    struct stat st;
    char *ptr_t,*ptr_bb,*query,*ptr_b=buf;
    int notcgi;//用于记录请求类型，是否是cgi

    if(rioreadnb(fd,buf,sizeof buf)<=0){
        //请求错误
        response_501(cfd);
        close(cfd);
        return NULL;
    }
    //读取类型
    /*    以下是一个简单请求 
     * "
     * GET /index.html HTTP/1.0\r\n
     * User-Agent: Happy is good.\r\n
     * Host: 127.0.0.1:312\r\n
     * Connection: close\r\n
     * \r\n
     *"
     */
    //提取 GET 等
    for(ptr_t=type,ptr_bb=ptr_b;!isspace(*ptr_bb)&&
            (ptr_t-type)<sizeof type -1;*ptr_t++=*ptr_bb++)
                ;
    //这里要判断一下到底是get还是post
    if((notcgi=strcasecmp(type,"POST")) && strcasecmp(type,"POST")){
        response_501(cfd);
        close(cfd);
        return NULL;
    }
    //
    //
    //取出多余的空格
    while(*ptr_bb && isspace(*ptr_bb))
        ++ptr_bb;
    //提取 /index.html 等信息，，并处理成实际地址
    *path='.';////当前目录
    for(ptr_t=path+1;(ptr_t-path)<sizeof path -1&&
            isspace(*ptr_bb);*ptr_t++=*ptr_bb++)
        ;
    *ptr_t='\0';//拼接完成！！！

    //依据请求的类型分别采用不同的操作
    //GET?POST：
    if(notcgi!=0){
        for(query=path;*query &&*query !='?';++query)
            //针对带参数的形式
            ;
        if(*query=='?'){
            notcgi=0;
            *query++='\0';
        }
    }
    //type,path,query都已经构建好了
    if((stat(path,&st)<0)){
        while(rio_readnb(cfd,buf,sizeof buf)>0 &&strcmp("\n",buf))
            ;//读取内容知道结束
        response_404(cfd);
        close(cfd);
        return NULL;
    }
    //合法情况下，执行，写入，读取权限
    if((st.st_mode&S_IXUSR)||(st.st_mode&S_IXGRP)||
            (st.st_mode&S_IXOTH))
        notcgi=0;//缺少权限
    if(notcgi)
        response_file(cfd,path);
    else
        response_cgi(cfd,path,type,query);
    close(cfd);
    return NULL;
}

/*
 * cgi处理客户端请求
 */
void response_cgi(int cfd,const char*path,const char*type,
        const char* query){
    char buf[_INT_BUF];
    int pocgi[2],piccgi[2];
    pid_t pid;
    int contlen=-1; //content length
    char c;

    /*    以下是一个简单请求 
     * "
     * GET /index.html HTTP/1.0\r\n
     * User-Agent: Happy is good.\r\n
     * Host: 127.0.0.1:312\r\n
     * Connection: close\r\n
     * \r\n
     *"
     */
 
    if(strcasecmp(type,"POST")==0){
        while(rio_readnb(cfd,buf,sizeof buf)>0&&
                strcmp("\n",buf)){
            buf[15]='\0';
            if(!strcase)
        }
        if(contlen==-1){
            response_400(cfd);//请求解析失败
            return;
        }
        else{
            //读取content，其实是与cgi执行无关的信息
            while(rio_readnb(cfd,buf,sizeof buf)>0 && strcmp("/n",buf))
                ;
        }
    }
    if(pipe(pocgi)<0){
        response_500(cfd);
        return;
    }
    if(pipe(picgi)<0){
        response_500(cfd);
        return;
    }
    //创建子进程
    if(pid=fork()<0){
        //创建失败
        close(pocgi[0]);
        close(pocgi[1]);
        close(picgi[0]);
        close(picgi[1]);
        response_500(cfd);
        return;
    }
    if(pid==0){
        /*子进程处理*/
        //重定向
        dup2(pocgi[1],1);//#STDOUT_FILENO
        dup2(pocgi[0],0);//STDIN_FILENO
        close(pocgi[0]);
        close(pocgi[1]);
        //环境变量设置
        spritf(buf,"REQUEST_METHOD=%s",type);
        putenv(buf);
        if(strcasecmp(buf,"POST")==0)
            srpintf(buf,"CONTENT_LENGTH=%d",contlen);
        else
            sprintf(buf,"QUERY_STRING=%s",query);
        putenv(buf);
        execl(path,path,NULL);
        exit(EXIT_SUCCESS);
    }
    /*父进程处理，主要负责响应信息回复*/
    rio_writen(cfd,"HTTP/1.0 200 OK\r\n",17);
    close(pocgi[1]);
    close(picgi[0]);

    if(strcasecmp(type,"POST")==0){
        int i;//将数据写入到picgi管道中,让子进程在picgi[0]中读取
        for(int i=0;i<conlen;++i){
            rio_readnb(cfd,&c,1);
            write(picgi[1],&c,1);
        }
    }
    while(rio_readnb(pocgi[0],&c,1)>0)
        rio_write(cfd,&c,1);
    close(pocgi[0]);
    close(picgi[1]);
    //等待子进程结束
    waitpid(pid,NULL,0);
    
}
