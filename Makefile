LIBS=-lpng
CFLAGS=-march=native -O2

all:
	$(CC) $(LIBS) main.c $(CFLAGS) -Wall -o tpng
