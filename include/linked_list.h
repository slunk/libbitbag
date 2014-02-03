/* linked_list.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <abstract/list.h>

typedef struct _list_entry {
    struct _list_entry *prev;
    struct _list_entry *next;
    void *data;
} list_entry_t;

typedef struct _linked_list_data {
    list_entry_t *head;
    list_entry_t *tail;
    int size;
    int (*keycmp)(void *a, void *b);
} linked_list_data_t;

list_t *linked_list_new();
void linked_list_add(void *data, void *elt);
void linked_list_del(void *data, void *elt);
void *linked_list_get(void *data, int idx);
void linked_list_set(void *data, int idx, void *elt);
int linked_list_search(void *data, void *elt);
int linked_list_size(void *data);
void linked_list_free(void *data);

#endif
