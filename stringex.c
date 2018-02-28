/*
  Copyright 2018 Brian Pow <brianpow@gmail.com>
  Licence: LGPL v3.0 or later
*/

#include "stringex.h"

errno_t dstrcat(char **dest, const char *src)
{
    rsize_t destSize = 0;
    if(*dest)
        destSize = msize(*dest);
    // printf("%s : %u\n", __func__, destSize);
    return dstrcat_s(dest, &destSize, src);
}

errno_t dstrcat_s(char **dest, rsize_t *destSize, const char *src)
{
    rsize_t sizeNeeded =strlen(src) + 1;
    if(*dest)
        sizeNeeded += strlen(*dest);
    char *newPtr = NULL;
    if(!*dest || sizeNeeded > *destSize)
    {
        if(newPtr = recalloc(*dest, sizeNeeded))
        {
            // printf("%s():, dest:%u, newPtr:%u, msize: %u, sizeNeeded:%u, *destSize:%u\n", __func__, *dest, newPtr,msize(newPtr), sizeNeeded, *destSize);
            *dest = newPtr;
            *destSize = sizeNeeded;
            // printf("%s():, *dest:%u, msize: %u, len: %u, *destSize:%u, src: %u\n", __func__, *dest, msize(*dest), strlen(*dest), *destSize, strlen(src));
            return strcat_s(*dest, *destSize, src);
        }
        return ENOMEM;
    }
    return strcat_s(*dest, *destSize, src);
}

errno_t dstrncat(char **dest, const char *src, rsize_t count)
{
    rsize_t destSize = 0;
    if(*dest)
        destSize = msize(*dest);
    // printf("%s() %u _Dst: %s, _DstSizeInChars: %u, _Src: %s\n", __func__ , __LINE__, *dest, destSize, src);
    return dstrncat_s(dest, &destSize, src, count);
}

errno_t dstrncat_s(char **dest, rsize_t *destSize, const char *src, rsize_t count)
{
    rsize_t newCount = (strlen(src) < count)? strlen(src) : count;
    // printf("%s() %u _Dst: %s, _DstSizeInChars: %u, _Src: %s, size: %u\n", __func__ , __LINE__, *dest, *destSize, src, -1);
    rsize_t sizeNeeded = newCount + 1 + ((*dest)? strlen(*dest): 0);
    char *newPtr = NULL;

    if(!*dest || sizeNeeded > *destSize)
    {
        if(newPtr = recalloc(*dest, sizeNeeded))
        {
            *dest = newPtr;
            *destSize = sizeNeeded;
            // printf("%s() %u _Dst: %s, _DstSizeInChars: %u, _Src: %s, newCount: %u\n", __func__ , __LINE__, *dest, *destSize, src, newCount);
            return strncat_s(*dest, *destSize, src, newCount);
        }
        return ENOMEM;
    }
    return strncat_s(*dest, *destSize, src, newCount);
}

errno_t dstrcpy(char **dest, const char *src)
{
    rsize_t destSize = 0;
    if(*dest)
        destSize = msize(*dest);
    return dstrcpy_s(dest, &destSize, src);
}

errno_t dstrcpy_s(char **dest, rsize_t *destSize, const char *src)
{
    rsize_t sizeNeeded = strlen(src) + 1;
    char *newPtr = NULL;
    // printf("%s() %u _Dst: %s, _DstSizeInChars: %u, _Src: %s, size: %u\n", __func__ , __LINE__, *dest, *destSize, src, sizeNeeded);
    if(!*dest || sizeNeeded > *destSize)
    {
        if(newPtr = recalloc(*dest, sizeNeeded))
        {
            *dest = newPtr;
            *destSize = sizeNeeded;
            return strcpy_s(*dest, *destSize, src);
        }
        return ENOMEM;
    }
    return strcpy_s(*dest, *destSize, src);
}

errno_t dstrncpy(char **dest, const char *src, rsize_t count)
{
    rsize_t destSize = 0;
    if(*dest)
        destSize = msize(*dest);
    return dstrncpy_s(dest, &destSize, src, count);
}

errno_t dstrncpy_s(char **dest, rsize_t *destSize, const char *src, rsize_t count)
{
    rsize_t newCount = (strlen(src) < count)? strlen(src) : count;
    rsize_t sizeNeeded = newCount + 1;
    char *newPtr = NULL;
    if(!*dest || sizeNeeded > *destSize)
    {
        if(newPtr = realloc(*dest, sizeNeeded))
        {
            *dest = newPtr;
            *destSize = sizeNeeded;
            // printf("%u: newPtr: %u, sizeNeeded: %u\n",__LINE__, newPtr, sizeNeeded);
            return strncpy_s(*dest, *destSize, src, newCount);
        }
        return ENOMEM;
    }
    return strncpy_s(*dest, *destSize, src, newCount);
}

int dsnprintf(char **dest, size_t *destSize, const char *format, ...)
{
    int retVal = 0;
    va_list args;
    va_start (args, format);
    retVal = dvsnprintf(dest, destSize, format, args);
    va_end (args);
    return retVal;
}

int dvsnprintf(char **dest, size_t *destSize, const char *format, va_list args)
{
    size_t sizeNeeded = 0;
    char *newPtr;
    sizeNeeded=1 + vsnprintf(NULL, 0, format, args);
    if(sizeNeeded > 1)
    {
        if(!*dest || sizeNeeded > *destSize)
            if(newPtr = realloc(*dest, sizeNeeded))
            {
                *dest = newPtr;
                *destSize = sizeNeeded;
            }
            else
                return ENOMEM;
        sizeNeeded = vsprintf(*dest, format, args);
        return sizeNeeded;
    }
    return sizeNeeded - 1;

}

int dvsprintf(char **dest, const char *format, va_list args)
{
    size_t destSize = 0;
    if(*dest)
        destSize = msize(*dest);
    return dvsnprintf(dest, &destSize, format, args);
}

int dsprintf(char **dest, const char *format, ...)
{
    int retVal;
    va_list args;
    va_start (args, format);
    retVal = dvsprintf(dest, format, args);
    va_end(args);
    return retVal;
}

//  _CRTIMP errno_t _dstrcpy_s(char **_Dst, rsize_t *_SizeInBytes, const char *_Src){
//      rsize_t size;
//      char *newPtr = NULL;
//      if(!*_Dst || !*_SizeInBytes || *_SizeInBytes < (size = strlen(_Src) + 1))
//      {
//         if(newPtr=realloc(*_Dst, size))
//         {
//             *_SizeInBytes=size;
//             *_Dst=newPtr;
//             return strcpy_s(*_Dst, *_SizeInBytes, _Src);
//         }
//         return ENOMEM;
//     }
//     return strcpy_s(*_Dst, *_SizeInBytes, _Src);
//  }

//  _CRTIMP errno_t _dstrcat_s(char **_Dst, rsize_t *_SizeInBytes, const char * _Src){
//     rsize_t size;
//      char *newPtr = NULL;
//      if(!*_Dst || !*_SizeInBytes || *_SizeInBytes < (size = strlen(_Src) + strlen(*_Dst) + 1))
//      {
//         if(newPtr=realloc(*_Dst, size))
//         {
//             *_SizeInBytes=size;
//             *_Dst=newPtr;
//             return strcat_s(*_Dst, *_SizeInBytes, _Src);
//         }
//         return ENOMEM;
//     }
//     return strcat_s(*_Dst, *_SizeInBytes, _Src);

//  }
// _CRTIMP errno_t _dstrncat_s(char **_Dst,size_t *_DstSizeInChars,const char *_Src,size_t _MaxCount)
// {
//     size_t srcSize = strlen(_Src);
//     srcSize = ((srcSize < _MaxCount)? srcSize: _MaxCount);
//     char *newPtr = NULL;
//     size_t size = 1 + strlen(*_Dst) + srcSize;
//     printf("%u _Dst: %s, _DstSizeInChars: %u, _Src: %s, size: %u\n", __LINE__, *_Dst, *_DstSizeInChars, _Src, srcSize);
//      if(!*_Dst || !*_DstSizeInChars || *_DstSizeInChars < size)
//      {
//         if(newPtr=realloc(*_Dst, size))
//         {
//             *_DstSizeInChars=size;
//             *_Dst=newPtr;
//             printf("%u _Dst: %s, _DstSizeInChars: %u, _Src: %s, size: %u\n", __LINE__, *_Dst, *_DstSizeInChars, _Src, srcSize);
//             return strncat_s(*_Dst, *_DstSizeInChars, _Src, srcSize);
//         }
//         return ENOMEM;
//     }
//     return strncat_s(*_Dst, *_DstSizeInChars, _Src, srcSize);
// }

// _CRTIMP errno_t _dstrncpy_s(char **_Dst,size_t *_DstSizeInChars,const char *_Src,size_t _MaxCount)
// {
//     size_t srcSize = strlen(_Src);
//     srcSize = ((srcSize < _MaxCount)? srcSize: _MaxCount);
//     char *newPtr = NULL;
//     size_t size = 1 + srcSize;
//     if(!*_Dst || !*_DstSizeInChars || *_DstSizeInChars < size)
//      {
//         if(newPtr=realloc(*_Dst, size))
//         {
//             *_DstSizeInChars=size;
//             *_Dst=newPtr;
//             printf("_Dst: %s, _DstSizeInChars: %u, _Src: %s, size: %u\n", *_Dst, *_DstSizeInChars, _Src, srcSize);
//             return strncpy_s(*_Dst, *_DstSizeInChars, _Src, srcSize);
//         }
//         return ENOMEM;
//     }
//     return strncpy_s(*_Dst, *_DstSizeInChars, _Src, size - 1);
// }

