/* bst_dict.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _BST_DICT_H
#define _BST_DICT_H

#include <abstract/dict.h>

typedef struct _bst_node {
    dict_entry_t entry;
    struct _bst_node *parent;
    struct _bst_node *left;
    struct _bst_node *right;
} bst_node_t;

typedef struct _bst_dict_data {
    bst_node_t *root;
    int size;
    int (*keycmp)(void *a, void *b);
} bst_dict_data_t;

dict_t *bst_dict_new(int (*keycmp)(void *a, void *b));
void *bst_dict_get(void *data, void *key);
void *bst_dict_get_key(void *data, void *key);
void bst_dict_put(void *data, void *key, void *val);
void bst_dict_del(void *data, void *key);
int bst_dict_size(void *data);
void bst_dict_free(void *data);

#endif
