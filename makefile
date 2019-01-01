all:serve

COM= -Wall -g -O0
CC=gcc -D_DEBUG

serve: serve.o response.o openlistenfd.o rioread.o 
	$(CC) $(COM) -o $@ $^ -lpthread 
serve.o:serve.c csapp.h macro.h
	$(CC) -c $< -lpthread 
response.o:response.c csapp.h macro.h
	$(CC) $(COM) -c $<
openlistenfd.o:openlistenfd.c csapp.h macro.h
	$(CC) $(COM) -c $<
rioread.o:rioread.c csapp.h macro.h
	$(CC) $(COM) -c $<


.PHONY:clean
clean:
	rm -i serve serve.o respone.o openlistenfd.o rioread.o
