# libbitbag

## What

A generic container library for C.

## Guide

### Code

1. Include the appropriate header files in your code. Example:

        #include <abstract/list.h>
        #include <linked_list.h>

2. Define a container as a pointer to an abstract container type. Initialize with a concrete "constructor." Example (list of C strings):

        int keycmp(void *a, void *b)
        {
            return strcmp((char *)a, (char *)b);
        }
        list_t *list = linked_list_new(keycmp);

3. Interact with containers with the macros defined in the abstract container's header file. Example:

        list_add(list, "foo");
        list_add(list, "bar");
        char *str = (char *)list_get(list, 0);

4. Free containers when they are no longer needed with the appropriate macro. Note: you are reponsible for freeing any dynamically allocated elements you store in the container. Example:

        list_free(list);

### Compilation

        > cd path/to/libcontainers
        > make
        > gcc -L path/to/libcontainers/lib -I path/to/libcontainers/include your_program.c
        > export LD_LIBRARY_PATH=path/to/libcontainers/lib (DYLD_LIBRARY_PATH on some unices)

## Todo

1. Iterators.
2. Hash table free.
3. (Push / pop) (front / back) for lists.
4. Thorough testing.
5. Self-balancing binary search tree.
6. Sorting.
7. Heap for priority queues?
8. Graphs?
