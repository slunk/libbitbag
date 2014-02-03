/* hash.h
 *
 * Copyright (C) 2014 Peter Enns
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */
#ifndef _HASH_H
#define _HASH_H

#include <stdint.h>

uint32_t super_fast_hash(const char * data, int len);

#endif
