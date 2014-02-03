/* bst_dict.c
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
#include <bst_dict.h>

int _bst_dict_default_keycmp(void *a, void *b)
{
    return (int)a - (int)b;
}

bst_node_t *_bst_dict_node(bst_node_t *parent, void *key, void *val)
{
    bst_node_t *rval = malloc(sizeof(*rval));
    rval->entry.key = key;
    rval->entry.val = val;
    rval->parent = parent;
    rval->left = NULL;
    rval->right = NULL;
    return rval;
}

bst_node_t *_bst_dict_find(bst_dict_data_t *data, void *key)
{
    bst_node_t *node = data->root;
    int cmp;
    while (node) {
        cmp = data->keycmp(key, node->entry.key);
        if (cmp < 0) {
            node = node->left;
        } else if (cmp > 0) {
            node = node->right;
        } else {
            return node;
        }
    }
    return NULL;
}

bst_node_t *_bst_dict_min(bst_node_t *node)
{
    if (!node->left)
        return node;
    return _bst_dict_min(node->left);
}

bst_node_t *_bst_dict_max(bst_node_t *node)
{
    if (!node->right)
        return node;
    return _bst_dict_max(node->right);
}

bst_node_t *_bst_dict_pred(bst_node_t *node)
{
    bst_node_t *parent = node->parent;
    if (node->left)
        return _bst_dict_min(node->left);
    while (parent) {
        if (parent->right == node)
            return parent;
        node = parent;
        parent = node->parent;
    };
    return NULL;
}

bst_node_t *_bst_dict_succ(bst_node_t *node)
{
    bst_node_t *parent = node->parent;
    if (node->right)
        return _bst_dict_min(node->right);
    while (parent) {
        if (parent->left == node)
            return parent;
        node = parent;
        parent = node->parent;
    };
    return NULL;
}

void _bst_dict_free_helper(bst_node_t *node)
{
    if (node) {
        _bst_dict_free_helper(node->left);
        _bst_dict_free_helper(node->right);
        free(node);
    }
}

dict_t *bst_dict_new(int (*keycmp)(void *a, void *b))
{
    dict_t *rval = malloc(sizeof(*rval));
    bst_dict_data_t *data = malloc(sizeof(*data));
    data->root = NULL;
    data->size = 0;
    data->keycmp = _bst_dict_default_keycmp;
    if (keycmp) {
        data->keycmp = keycmp;
    }
    rval->data = data;
    rval->get = bst_dict_get;
    rval->get_key = bst_dict_get_key;
    rval->put = bst_dict_put;
    rval->del = bst_dict_del;
    rval->size = bst_dict_size;
    rval->free = bst_dict_free;
    return rval;
}

void *bst_dict_get(void *data, void *key)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    bst_node_t *node = _bst_dict_find(bstdata, key);
    if (node)
        return node->entry.val;
    return NULL;
}

void *bst_dict_get_key(void *data, void *key)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    bst_node_t *node = _bst_dict_find(bstdata, key);
    if (node)
        return node->entry.key;
    return NULL;
}

void bst_dict_put(void *data, void *key, void *val)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    bst_node_t *node = bstdata->root;
    int cmp;
    if (!node) {
        bstdata->root = _bst_dict_node(NULL, key, val);
        bstdata->size++;
    }
    while (node) {
        cmp = bstdata->keycmp(key, node->entry.key);
        if (cmp < 0) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = _bst_dict_node(node, key, val);
                bstdata->size++;
                break;
            }
        } else if (cmp > 0) {
            if (node->right) {
                node = node->right;
            } else {
                node->right = _bst_dict_node(node, key, val);
                bstdata->size++;
                break;
            }
        } else {
            node->entry.val = val;
            break;
        }
    }
}

void bst_dict_del(void *data, void *key)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    bst_node_t *node = _bst_dict_find(bstdata, key);
    bst_node_t *succ;
    if (!node)
        return;
    if (node->left && node->right) {
        succ = _bst_dict_succ(node);
        node->entry.key = succ->entry.key;
        node->entry.val = succ->entry.val;
        node = succ;
    }
    if (node->left) {
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
        } else {
            bstdata->root = node->left;
        }
    } else if (node->right) {
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
        } else {
            bstdata->root = node->right;
        }
    } else {
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        } else {
            bstdata->root = NULL;
        }
    }
    free(node);
}

int bst_dict_size(void *data)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    return bstdata->size;
}

void bst_dict_free(void *data)
{
    bst_dict_data_t *bstdata = (bst_dict_data_t *)data;
    _bst_dict_free_helper(bstdata->root);
    free(bstdata);
}
