all:client

client:client.h macro.h openclientfd.c client.c
	gcc -Og -g -Wall -o client client.h macro.h client.c macro.h openclientfd.c

.PHONY: clean

clean:
	rm -i client
