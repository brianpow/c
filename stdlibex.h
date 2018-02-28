/*
  Copyright 2018 Brian Pow <brianpow@gmail.com>
  Licence: LGPL v3.0 or later
*/

#ifndef _INC_STDLIBEX
#define _INC_STDLIBEX

#include <stdlib.h>
#include <memory.h>

void *recalloc(void *_Memory, size_t _NewSize);
size_t msize(void *ptr);

#endif