#CFLAGS=-std=c11 -Wall -pedantic -Wextra -Werror
INCLUDE=../include
CSOURCES=list.c vector.c linked_list.c dict.c bst_dict.c hash_table.c hash.c
OBJECTS=$(CSOURCES:.c=.o)

all: libbitbag.so test

test: libbitbag.so main.c
	$(CC) $(CFLAGS) -L . -I $(INCLUDE) -lbitbag main.c -o test

libbitbag.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o libbitbag.so $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@ 

clean:
	rm -rf *.o *.so test
