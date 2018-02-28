/*
  Copyright 2018 Brian Pow <brianpow@gmail.com>
  Licence: LGPL v3.0 or later
*/

#include "stdlibex.h"

void *__cdecl recalloc(void *ptr, size_t newSize)
{
    size_t oldSize = 0;
    if(ptr)
        oldSize = msize(ptr);
    ptr = realloc(ptr, newSize);
    if(ptr != NULL && newSize > oldSize)
        memset(ptr + oldSize, 0, newSize - oldSize);
    return ptr;
}

size_t msize(void *ptr)
{
#ifdef _WIN32
    return _msize(ptr);
#elif __APPLE__
    return malloc_size(ptr);
#elif __linux__
    return malloc_usable_size(ptr);
#elif __unix__
    return malloc_usable_size(ptr);
#else
#error "Unknown target, msize() does not work."
#endif
}

