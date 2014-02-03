#CFLAGS=-std=c11 -Wall -pedantic -Wextra -Werror
INCLUDE=../include
CSOURCES=list.c vector.c linked_list.c dict.c bst_dict.c hash_table.c hash.c
OBJECTS=$(CSOURCES:.c=.o)

all: libcontainers.so test

test: libcontainers.so main.c
	$(CC) $(CFLAGS) -L . -I $(INCLUDE) -lcontainers main.c -o test

libcontainers.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o libcontainers.so $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ 

clean:
	rm -rf *.o *.so test
