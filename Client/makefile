all:client

COM = -Og -ggdb -Wall

CC = gcc

client:client.o openclientfd.o rioread.o
	$(CC) $(COM) -o $@ $^

client.o:client.c macro.h client.h openclientfd.h rioread.h
	$(CC) $(COM) -c $< macro.h client.h openclientfd.h rioread.h

openclientfd.o:openclientfd.c macro.h openclientfd.h 	
	$(CC) $(COM) -c $<

rioread.o:rioread.c rioread.h
	$(CC) $(COM) -c $<

.PHONY: clean

clean:
	rm -i client *.o 
