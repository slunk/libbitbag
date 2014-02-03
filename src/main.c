/* main.c
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#include <stdio.h>
#include <abstract/list.h>
#include <vector.h>
#include <linked_list.h>
#include <bst_dict.h>
#include <hash_table.h>
#include <hash.h>

#include <stdlib.h>
#include <string.h>

int str_keycmp(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int str_hash_fn(void *key)
{
    return super_fast_hash((char *)key, strlen((char *)key));
}

int main()
{
    list_t *list = linked_list_new(NULL);
    //dict_t *dict = bst_dict_new(str_keycmp);
    dict_t *dict = hash_table_new(str_keycmp, str_hash_fn);
    long int i;
    for (i = 0; i < 512; i++) {
        list_add(list, i);
    }
    printf("%d\n", list_size(list));
    printf("%d\n", list_search(list, 1));
    list_del(list, 1);
    printf("%d\n", list_search(list, 1));
    list_free(list);

    dict_put(dict, "hey", 99);
    dict_put(dict, "there", 63);
    printf("%d\n", (int)dict_get(dict, "there"));
    /*dict_free(dict);*/
    return 0;
}
