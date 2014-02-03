/* linked_list.c
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
#include <linked_list.h>

int _linked_list_default_keycmp(void *a, void *b)
{
    return (int)a - (int)b;
}

list_t *linked_list_new(int (*keycmp)(void *a, void *b))
{
    list_t *rval = malloc(sizeof(*rval));
    linked_list_data_t *data = malloc(sizeof(*data));
    data->head = NULL;
    data->tail = NULL;
    data->size = 0;
    data->keycmp = _linked_list_default_keycmp;
    if (keycmp)
        data->keycmp = keycmp;
    rval->data = data;
    rval->add = linked_list_add;
    rval->del = linked_list_del;
    rval->get = linked_list_get;
    rval->set = linked_list_set;
    rval->search = linked_list_search;
    rval->size = linked_list_size;
    rval->free = linked_list_free;
    return rval;
}

void linked_list_add(void *data, void *elt)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry = malloc(sizeof(*entry));
    entry->prev = lldat->tail;
    entry->next = NULL;
    entry->data = elt;
    if (lldat->tail) {
        lldat->tail->next = entry;
    } else {
        lldat->head = entry;
    }
    lldat->tail = entry;
    lldat->size++;
}

void linked_list_del(void *data, void *elt)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry;
    int i = linked_list_search(data, elt);
    if (i < 0)
        return;
    for (entry = lldat->head; entry != NULL; entry = entry->next) {
        if (!i--)
            break;
    }
    if (entry->prev) {
        entry->prev->next = entry->next;
    } else {
        lldat->head = entry->next;
    }
    if (entry->next) {
        entry->next->prev = entry->prev;
    } else {
        lldat->tail = entry->prev;
    }
    lldat->size--;
    free(entry);
}

void *linked_list_get(void *data, int idx)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry;
    if (idx < 0 || idx > lldat->size)
        return NULL;
    for (entry = lldat->head; entry != NULL; entry = entry->next) {
        if (!idx)
            break;
    }
    return entry->data;
}

void linked_list_set(void *data, int idx, void *elt)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry;
    if (idx < 0 || idx >= lldat->size)
        return;
    for (entry = lldat->head; entry != NULL; entry = entry->next) {
        if (!idx)
            break;
    }
    entry->data = elt;
}

int linked_list_search(void *data, void *elt)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry;
    int i = 0;
    for (entry = lldat->head; entry != NULL; entry = entry->next) {
        if (!lldat->keycmp(entry->data, elt))
            return i;
        i++;
    }
    return -1;
}

int linked_list_size(void *data)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    return lldat->size;
}

void linked_list_free(void *data)
{
    linked_list_data_t *lldat = (linked_list_data_t *)data;
    list_entry_t *entry;
    for (entry = lldat->head; entry != NULL; entry = entry->next) {
        free(entry);
    }
    free(lldat);
}
