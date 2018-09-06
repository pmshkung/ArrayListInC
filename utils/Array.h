#ifndef __ARRAY_H__
#define __ARRAY_H__

typedef struct _Array Array;

typedef struct _Array {
   void     *data;
   int      length;
} Array;

#define Array(elementType) Array

#endif /* __ARRAY_H__ */
