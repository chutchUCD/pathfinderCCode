src = $(wildcard *.c)
obj = $(src:.c =.o)
CLAGS = -O3

all.a: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)
	
list.o:
	$(CC) -c list.c $(CFLAGS)
	