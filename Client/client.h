#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

/*定义用于拼接的head*/
#define STR_HEAD_1 "GET /index.html HTTP/1.0\r\n \
    User-Agent:Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0.\r\n \
    Host:127.0.0.1:)"
#define STR_HEAD_2 "\r\n \
    Connection:close\r\n \
    \r\n"

