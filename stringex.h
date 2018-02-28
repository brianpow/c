/*
  Copyright 2018 Brian Pow <brianpow@gmail.com>
  Licence: LGPL v3.0 or later
*/

#ifndef _INC_STRINGEX
#define _INC_STRINGEX

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "stdlibex.h"

errno_t dstrcat(char **dest, const char *src);
errno_t dstrncat(char **dest, const char *src, rsize_t count);
errno_t dstrcpy(char **dest, const char *src);
errno_t dstrncpy(char **dest, const char *src, rsize_t count);
errno_t dstrcpy_s(char **dest, rsize_t *destSize, const char *src);
errno_t dstrcat_s(char **dest, rsize_t *destSize, const char * src);
errno_t dstrncat_s(char **dest, rsize_t *destSize, const char *src, rsize_t count);
errno_t dstrncpy_s(char **dest, rsize_t *destSize, const char *src, rsize_t count);
int dsprintf(char **dest, const char *format, ...);
int dvsprintf(char **dest, const char *format, va_list args);
int dsnprintf(char **dest, size_t *destSize, const char *format, ...);
int dvsnprintf(char **dest, size_t *destSize, const char *format, va_list args);

#endif