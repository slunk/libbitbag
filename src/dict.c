/* dict.c
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#include <stdlib.h>
#include <abstract/dict.h>

void *_dict_get(dict_t *dict, void *key)
{
    return dict->get(dict->data, key);
}

/*
 * Okay, so why? Honestly, I'm not sure this is necessary, but
 * if someone uses dynamically allocated keys, they might need
 * to be able to access them to free them... maybe?
 */
void *_dict_get_key(dict_t *dict, void *key)
{
    return dict->get_key(dict->data, key);
}

void _dict_put(dict_t *dict, void *key, void *val)
{
    dict->put(dict->data, key, val);
}

void _dict_del(dict_t *dict, void *key)
{
    dict->del(dict->data, key);
}

int _dict_size(dict_t *dict)
{
    return dict->size(dict->data);
}

void _dict_free(dict_t *dict)
{
    dict->free(dict->data);
    free(dict);
}

int _dict_keycmp(void *a, void *b)
{
    dict_entry_t *aentry = (dict_entry_t *)a;
    dict_entry_t *bentry = (dict_entry_t *)b;
    return aentry->keycmp(aentry->key, bentry->key);
}
