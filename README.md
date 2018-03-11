# Extended libraries for c

## stdlibex

Added recalloc()

## stringex

Added dstrcat(), dstrncat(), dstrcpy(), dstrncpy(), dstrcpy_s(), dstrcat_s(), dstrncat_s(), dstrncpy_s(), dsprintf(), dvsprintf(), dsnprintf() and dvsnprintf()

Heap string will be dynamically adjusted if the size is too small. Never use stack string please.

### Examples

```c
char *buff = NULL; //Important to initialize your variable!
errno_t err = 0; //Important to initialize your variable!
err=dstrcat(&buff, "12345"); //Yeah! buff will be adjusted if the size is not enough. No more overflow, no more crash!
```

```c
char *buff = NULL;
size_t size=0;
errno_t err = 0;
dsnprintf(&buff, &size, "%d %d %s",1,2, "Test");
```

## Note

Non-standard _msize()/malloc_size()/malloc_usable_size() function is used to check the allocated size, it may break portability
