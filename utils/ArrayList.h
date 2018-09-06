#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/Array.h"

typedef struct _ArrayList ArrayList;

typedef ArrayList*   (*CreateWithSize)(int elementTypeSize, int size);
typedef void         (*Init)(int elementTypeSize, ArrayList* outArrayList);

typedef int          (*Size)(ArrayList* arrayList);
typedef void*        (*Get)(ArrayList* arrayList, int index);
typedef void*        (*Add)(ArrayList* arrayList, void* elementPtr);
typedef void         (*AddArray)(ArrayList* arrayList, void *data, int length, int elementTypeSize);
typedef void*        (*Insert)(ArrayList* arrayList, int index, void* elementPtr);
typedef void*        (*Pop)(ArrayList* arrayList);
typedef void         (*Remove)(ArrayList* arrayList, int index);
typedef void         (*RemoveRange)(ArrayList* arrayList, int fromIndex, int toIndex);
typedef void         (*RemoveByLast)(ArrayList* arrayList, int index);
typedef void         (*Clear)(ArrayList* arrayList);
typedef void         (*Release)(ArrayList** const arrayList);

#define ArrayList(elementType)                        ArrayList

#define ARRAYLIST(P, TYPE)                            *P
#define ARRAYLIST_NEW(TYPE)                           newArrayList(sizeof(TYPE))
#define ARRAYLIST_SIZE(P)                             P->fptrSize(P)
#define ARRAYLIST_GET(P, INDEX, TYPE)                 *((TYPE*)P->fptrGet(P, INDEX))
#define ARRAYLIST_ADD(P, DATA)                        P->fptrAdd(P, DATA)
#define ARRAYLIST_ADD_ARRAY(P, DATA, LENGTH, TYPE)    P->fptrAddArray(P, DATA, LENGTH, sizeof(TYPE))
#define ARRAYLIST_INSERT(P, INDEX, DATA)              P->fptrInsert(P, INDEX, DATA)
#define ARRAYLIST_POP(P)                              P->fptrPop(P)
#define ARRAYLIST_REMOVE(P, INDEX)                    P->fptrRemove(P, INDEX)
#define ARRAYLIST_REMOVE_RANGE(P, FROM, TO)           P->fptrRemoveRange(P, FROM, TO)
#define ARRAYLIST_REMOVE_BY_LAST(P, INDEX)            P->fptrRemoveByLast(P, INDEX)
#define ARRAYLIST_RELEASE(P)                          P->fptrRelease(&P)

typedef struct _ArrayList {
   int                     increase;
   int                     elementTypeSize;
   int                     size;

   Array(elementType)      elementArray[1];

   Size                    fptrSize;
   Get                     fptrGet;

   Add                     fptrAdd;
   AddArray                fptrAddArray;
   Insert                  fptrInsert;

   Pop                     fptrPop;
   Remove                  fptrRemove;
   RemoveRange             fptrRemoveRange;
   RemoveByLast            fptrRemoveByLast;

   Clear                   fptrClear;
   Release                 fptrRelease;

} ArrayList;

ArrayList* newArrayList(int elementTypeSize);
void freeArrayList(ArrayList** const arrayList);

#endif /* __ARRAYLIST_H__ */
 
