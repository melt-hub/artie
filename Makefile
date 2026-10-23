
# ----------+ FLAGS +----------
CFLAGS= -O2 -Wall -Wextra
CC= gcc

artie : main.c
	$(CC) $(CFLAGS) -o artie main.c