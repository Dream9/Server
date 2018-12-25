//辅助变量与宏
//

//
//调试信息设置
//在makefile中写了，这里忘了。。。。
#ifdef _DEBUG_FILE

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
           DebugMsg(#return_code);exit(EXIT_FAILURE);\
       }
    #ifdef _RELEASE 
        //发行版本，什么也不做
        #define DebugMsg(fmt)  
    #else
        #define DebugMsg(fmt, ...) \
            fprintf(stderr,"[%s:%s:%d][error%d:%s]"fmt"\r\n",__FILE__,__FUNCTION__, \
                    __LINE__,errno,strerror(errno)##__VA_ARGS__);
    #endif

#endif

