
# ----------+ FLAGS +----------
CFLAGS= -O2 -Wall -Wextra
CC= gcc
LIB= -lsqlite3

artie : main.c
	$(CC) $(CFLAGS) -o artie main.c $(LIB)