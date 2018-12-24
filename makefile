all:main

main: serve.o response.o openlistenfd.o rioread.o 
	gcc -D_DEBUG  -Wall -lpthread -g -o main $@ $^
serve.o:serve.c csapp.h
	gcc -D_DEBUG -Wall -lpthread -g -c serve.c csapp.h
response.o:response.c csapp.h
	gcc -D_DEBUG -Wall -g -c response.c csapp.h
openlistenfd.o:openlistenfd.c csapp.h
	gcc -D_DEBUG -Wall -g -c openlistenfd.c csapp.h
rioread.o:rioread.c csapp.h
	gcc -D_DEBUG -Wall -g -c rioread.c csapp.h
.PHONY:clean
clean:
	rm serve.o respone.o openlistenfd.o
