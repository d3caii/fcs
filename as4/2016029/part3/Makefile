EXE=passwd
CC=gcc
CFLAGS=-lssl -lcrypto#Incase you need it

$(EXE): main.c password.o # You can make it scarrier by using $< and @ (google)
	$(CC) main.c passwd.o -o $(EXE) $(CFLAGS)

password.o: passwd.c passwd.h
	$(CC) -c passwd.c $(CFLAGS)
main.o : main.c # this too works

bruteforce: bruteforce.c
	$(CC) bruteforce.c -o bruteforce

.PHONY:clean

clean: 
	rm -f *.o $(EXE)


