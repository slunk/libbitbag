/* hash_table.c
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <abstract/dict.h>
#include <abstract/list.h>
#include <hash_table.h>
#include <linked_list.h>

list_t *_hash_table_get_list(hash_table_data_t *htdat, void *key)
{
    int idx = (uint32_t)htdat->hash_fn(key) % htdat->table_size;
    return (list_t *)htdat->table[idx];
}

dict_entry_t *_hash_table_get_entry(hash_table_data_t *htdat, void *key)
{
    list_t *list = _hash_table_get_list(htdat, key);;
    dict_entry_t query = {
        .key = key,
        .keycmp = htdat->keycmp,
    };
    int idx;
    if (!list)
        return NULL;
    idx = list_search(list, &query);
    dict_entry_t *entry = NULL;
    if (idx >= 0) {
        entry = (dict_entry_t *)list_get(list, idx);
        return entry;
    }
    return NULL;
}

dict_t *hash_table_new(int (*keycmp)(void *a, void *b), int (*hash_fn)(void *a))
{
    dict_t *rval = malloc(sizeof(*rval));
    hash_table_data_t *data = malloc(sizeof(*data));
    data->table_size = HASH_TABLE_INIT_SIZE;
    data->table = malloc(data->table_size * sizeof(*data->table));
    memset(data->table, 0, data->table_size * sizeof(*data->table));
    data->size = 0;
    data->keys = linked_list_new(keycmp);
    data->hash_fn = hash_fn;
    data->keycmp = keycmp;
    rval->data = data;
    rval->get = hash_table_get;
    rval->get_key = hash_table_get_key;
    rval->put = hash_table_put;
    rval->del = hash_table_del;
    rval->size = hash_table_size;
    rval->free = hash_table_free;
    return rval;
}

void *hash_table_get(void *data, void *key)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    dict_entry_t *entry = _hash_table_get_entry(htdat, key);
    if (entry)
        return entry->val;
    return NULL;
}

void *hash_table_get_key(void *data, void *key)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    dict_entry_t *entry = _hash_table_get_entry(htdat, key);
    if (entry)
        return entry->key;
    return NULL;
}

void hash_table_put(void *data, void *key, void *val)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    dict_entry_t *entry = _hash_table_get_entry(htdat, key);
    list_t *list;
    uint32_t idx;
    if (entry) {
        entry->val = val;
    } else {
        entry = malloc(sizeof(*entry));
        entry->key = key;
        entry->val = val;
        entry->keycmp = htdat->keycmp;
        list = _hash_table_get_list(htdat, key);
        if (!list) {
            idx = (uint32_t)htdat->hash_fn(key) % htdat->table_size;
            printf("idx: %d\n", idx);
            list = linked_list_new(_dict_keycmp);
            htdat->table[idx] = list;
        }
        list_add(htdat->keys, key);
        list_add(list, entry);
        htdat->size++;
    }
}

void hash_table_del(void *data, void *key)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    list_t *list = _hash_table_get_list(htdat, key);
    dict_entry_t *entry = _hash_table_get_entry(htdat, key);
    if (list && entry) {
        list_del(list, entry);
        list_del(htdat->keys, key);
        htdat->size--;
    }
}

int hash_table_size(void *data)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    return htdat->size;
}

void hash_table_free(void *data)
{
    hash_table_data_t *htdat = (hash_table_data_t *)data;
    /* TODO: implement
     * Need some sort of list iterator first.
     */
}
