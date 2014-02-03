/* abstract/list.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _LIST_H
#define _LIST_H

typedef struct _list {
    void *data;
    void (*add)(void *data, void *elt);
    void (*del)(void *data, void *elt);
    void *(*get)(void *data, int i);
    void (*set)(void *data, int i, void *elt);
    int (*search)(void *data, void *elt);
    int (*size)(void *data);
    void (*free)(void *data);
} list_t;

void _list_add(list_t *list, void *elt);
void _list_del(list_t *list, void *elt);
void *_list_get(list_t *list, int i);
void _list_set(list_t *list, int i, void *elt);
int _list_search(list_t *list, void *elt);
int _list_size(list_t *list);
void _list_free(list_t *list);

#define list_add(list, elt) _list_add(list, (void *)elt)
#define list_del(list, elt) _list_del(list, (void *)elt);
#define list_get(list, idx) _list_get(list, idx)
#define list_set(list, idx, elt) _list_set(list, idx, (void *)elt)
#define list_search(list, elt) _list_search(list, (void *)elt)
#define list_size(list) _list_size(list)
#define list_free(list) _list_free(list);

#endif
