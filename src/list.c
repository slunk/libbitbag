/* list.c
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

void _list_add(list_t *list, void *elt)
{
    list->add(list->data, elt);
}

void _list_del(list_t *list, void *elt)
{
    list->del(list->data, elt);
}

void *_list_get(list_t *list, int i)
{
    return list->get(list->data, i);
}

void _list_set(list_t *list, int i, void *elt)
{
    list->set(list->data, i, elt);
}

int _list_search(list_t *list, void *elt)
{
    return list->search(list->data, elt);
}

int _list_size(list_t *list)
{
    return list->size(list->data);
}

void _list_free(list_t *list)
{
    list->free(list->data);
    free(list);
}
