/* vector.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _VECTOR_H
#define _VECTOR_H

#include <abstract/list.h>

#define VECTOR_INIT_SIZE 256

typedef struct _vector_data {
    int size;
    int last;
    void **arr;
} vector_data_t;

list_t *vector_new();
void vector_add(void *data, void *elt);
void vector_del(void *data, void *elt);
void *vector_get(void *data, int idx);
void vector_set(void *data, int idx, void *elt);
int vector_search(void *data, void *elt);
int vector_size(void *data);
void vector_free(void *data);

#endif
