/* vector.c
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#include <stdlib.h>
#include <abstract/list.h>
#include <vector.h>

list_t *vector_new()
{
    list_t *rval = malloc(sizeof(*rval));
    vector_data_t *data = malloc(sizeof(*data));
    data->arr = malloc(VECTOR_INIT_SIZE * sizeof(*data->arr));
    data->size = VECTOR_INIT_SIZE;
    data->last = 0;
    rval->data = data;
    rval->add = vector_add;
    rval->del = vector_del;
    rval->get = vector_get;
    rval->set = vector_set;
    rval->search = vector_search;
    rval->size = vector_size;
    rval->free = vector_free;
    return rval;
}

void vector_add(void *data, void *elt)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    int i;
    void **grown;
    if (vecdat->last >= vecdat->size) {
        vecdat->size *= 2;
        grown = malloc(vecdat->size * sizeof(*vecdat->arr));
        for (i = 0; i < vecdat->last; i++) {
            grown[i] = vecdat->arr[i];
        }
        free(vecdat->arr);
        vecdat->arr = grown;
    }
    vecdat->arr[vecdat->last++] = elt;
}

void vector_del(void *data, void *elt)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    int i;
    for (i = vector_search(data, elt) + 1; i > 0 && i < vecdat->last; i++) {
        vecdat->arr[i - 1] = vecdat->arr[i];
    }
    if (i == vecdat->last)
        vecdat->last--;
}

void *vector_get(void *data, int idx)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    if (idx >= 0 || idx < vecdat->last) {
        return vecdat->arr[idx];
    }
    return NULL;
}

void vector_set(void *data, int idx, void *elt)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    if (idx >= 0 || idx < vecdat->last) {
        vecdat->arr[idx] = elt;
    }
}

int vector_search(void *data, void *elt)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    int i;
    for (i = 0; i < vecdat->last; i++) {
        if (vecdat->arr[i] == elt)
            return i;
    }
    return -1;
}

int vector_size(void *data)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    return vecdat->last;
}

void vector_free(void *data)
{
    vector_data_t *vecdat = (vector_data_t *)data;
    free(vecdat->arr);
    free(vecdat);
}
