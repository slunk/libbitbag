/* abstract/dict.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _DICT_H
#define _DICT_H

typedef struct _dict_entry {
    void *key;
    void *val;
    int (*keycmp)(void *a, void *b);
} dict_entry_t;

typedef struct _dict {
    void *data;
    void *(*get)(void *data, void *key);
    void *(*get_key)(void *data, void *key);
    void (*put)(void *data, void *key, void *val);
    void (*del)(void *data, void *key);
    int (*size)(void *data);
    void (*free)(void *data);
} dict_t;

void *_dict_get(dict_t *dict, void *key);
void *_dict_get_key(dict_t *dict, void *key);
void _dict_put(dict_t *dict, void *key, void *val);
void _dict_del(dict_t *dict, void *key);
int _dict_size(dict_t *dict);
void _dict_free(dict_t *dict);
int _dict_keycmp(void *a, void *b);

#define dict_get(dict, key) _dict_get(dict, (void *)key)
#define dict_get_key(dict, key) _dict_get_key(dict, (void *)key)
#define dict_put(dict, key, val) _dict_put(dict, (void *)key, (void *)val)
#define dict_del(dict, key) _dict_del(dict, (void *)key)
#define dict_size(dict) _dict_size(dict)
#define dict_free(dict) _dict_free(dict)

#endif
