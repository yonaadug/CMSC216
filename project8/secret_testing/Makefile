CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow

all: secret01.x secret02.x secret03.x secret04.x secret05.x secret06.x \
	secret07.x secret08.x secret09.x secret10.x secret11.x secret12.x \
	secret13.x secret14.x secret15.x   

secret01.x: secret01.o unix.o
	$(CC) secret01.o unix.o -o secret01.x

secret02.x: secret02.o unix.o
	$(CC) secret02.o unix.o -o secret02.x

secret03.x: secret03.o unix.o
	$(CC) secret03.o unix.o -o secret03.x

secret04.x: secret04.o unix.o
	$(CC) secret04.o unix.o -o secret04.x

secret05.x: secret05.o unix.o
	$(CC) secret05.o unix.o -o secret05.x

secret06.x: secret06.o unix.o
	$(CC) secret06.o unix.o -o secret06.x

secret07.x: secret07.o unix.o
	$(CC) secret07.o unix.o -o secret07.x

secret08.x: secret08.o unix.o
	$(CC) secret08.o unix.o -o secret08.x

secret09.x: secret09.o unix.o
	$(CC) secret09.o unix.o -o secret09.x

secret10.x: secret10.o unix.o driver.o
	$(CC) secret10.o unix.o driver.o -o secret10.x

secret11.x: secret11.o unix.o
	$(CC) secret11.o unix.o -o secret11.x

secret12.x: secret12.o unix.o
	$(CC) secret12.o unix.o -o secret12.x

secret13.x: secret13.o unix.o
	$(CC) secret13.o unix.o -o secret13.x

secret14.x: secret14.o unix.o
	$(CC) secret14.o unix.o -o secret14.x

secret15.x: secret15.o unix.o
	$(CC) secret15.o unix.o -o secret15.x

unix.o: unix.c unix.h unix-datastructure.h
	$(CC) $(CFLAGS) -c unix.c

secret01.o: secret01.c unix.h
	$(CC) $(CFLAGS) -c secret01.c

secret02.o: secret02.c unix.h
	$(CC) $(CFLAGS) -c secret02.c

secret03.o: secret03.c unix.h
	$(CC) $(CFLAGS) -c secret03.c

secret04.o: secret04.c unix.h
	$(CC) $(CFLAGS) -c secret04.c

secret05.o: secret05.c unix.h
	$(CC) $(CFLAGS) -c secret05.c

secret06.o: secret06.c unix.h
	$(CC) $(CFLAGS) -c secret06.c

secret07.o: secret07.c unix.h
	$(CC) $(CFLAGS) -c secret07.c

secret08.o: secret08.c unix.h
	$(CC) $(CFLAGS) -c secret08.c

secret09.o: secret09.c unix.h
	$(CC) $(CFLAGS) -c secret09.c

secret10.o: secret10.c unix.h driver.h
	$(CC) $(CFLAGS) -c secret10.c

secret11.o: secret11.c unix.h
	$(CC) $(CFLAGS) -c secret11.c

secret12.o: secret12.c unix.h
	$(CC) $(CFLAGS) -c secret12.c

secret13.o: secret13.c unix.h
	$(CC) $(CFLAGS) -c secret13.c

secret14.o: secret14.c unix.h
	$(CC) $(CFLAGS) -c secret14.c

secret15.o: secret15.c unix.h
	$(CC) $(CFLAGS) -c secret15.c

clean:
	rm -f secret*.x secret*.o unix.o
