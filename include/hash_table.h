/* hash_table.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _hash_table_H
#define _hash_table_H

#include <abstract/dict.h>
#include <abstract/list.h>

#define HASH_TABLE_INIT_SIZE 512

typedef struct _hash_table_data {
    void **table;
    int table_size;
    int size;
    list_t *keys;
    int (*hash_fn)(void *a);
    int (*keycmp)(void *a, void *b);
} hash_table_data_t;

dict_t *hash_table_new(int (*keycmp)(void *a, void *b), int (*hash_fn)(void *a));
void *hash_table_get(void *data, void *key);
void *hash_table_get_key(void *data, void *key);
void hash_table_put(void *data, void *key, void *val);
void hash_table_del(void *data, void *key);
int hash_table_size(void *data);
void hash_table_free(void *data);

#endif
