#include "../utils/ArrayList.h"

static void initArrayList(int elementTypeSize, ArrayList* outArrayList)
{
   outArrayList->elementArray->data = NULL;
   outArrayList->elementArray->length = 0;
   outArrayList->elementTypeSize = elementTypeSize;
   outArrayList->size = 0;
   outArrayList->increase = 20;
}

static inline void AddCapacity(ArrayList* arrayList, int increase)
{
   void *data;

   if (increase <= 0)
   {
      return;
   }

   data = realloc(arrayList->elementArray->data, (increase + arrayList->elementArray->length) * arrayList->elementTypeSize);
   if (NULL != data)
   {
      arrayList->elementArray->data = data;
      arrayList->elementArray->length += increase;
   }
}

static void* GetAdd(ArrayList* arrayList)
{
   if (arrayList->size == arrayList->elementArray->length)
   {
      AddCapacity(arrayList, arrayList->increase);
   }

   return (char *)arrayList->elementArray->data + arrayList->elementTypeSize * (arrayList->size++);
}

static void* GetInsert(ArrayList* arrayList, int index)
{
   void *from, *to;

   if (arrayList->size == arrayList->elementArray->length)
   {
      AddCapacity(arrayList, arrayList->increase);
   }

   from = (char *)arrayList->elementArray->data + arrayList->elementTypeSize * index;
   to = (char *)from + arrayList->elementTypeSize;

   memmove(to, from, arrayList->elementTypeSize * (arrayList->size - index));
   arrayList->size++;

   return from;
}

static int instanceSize(ArrayList* arrayList) {
   return arrayList->size;
}

static void* instanceGet(ArrayList* arrayList, int index) {
   if (index >= 0 && index < arrayList->size) {
      return (void *)((char *)arrayList->elementArray->data + arrayList->elementTypeSize * index);
   }

   return NULL;
}

static void* instanceAdd(ArrayList* arrayList, void *elementPtr)
{
   return memcpy(GetAdd(arrayList), elementPtr, arrayList->elementTypeSize);
}

static void instanceAddArray(ArrayList* arrayList, void *data, int length, int elementTypeSize)
{
   int num;
   if (arrayList->elementTypeSize != elementTypeSize)
   {
      return;
   }

   num = arrayList->elementArray->length - arrayList->size - length;
   if (num < 0)
   {
      AddCapacity(arrayList, -num + arrayList->increase);
   }

   memcpy(((char *)arrayList->elementArray->data + elementTypeSize * arrayList->size), data, elementTypeSize * length);

   arrayList->size += length;
}

static void* instanceInsert(ArrayList* arrayList, int index, void *elementPtr)
{
   return memcpy(GetInsert(arrayList, index), elementPtr, arrayList->elementTypeSize);
}

static void* instancePop(ArrayList *arrayList) {
   if (arrayList->size > 0) {
      return (char*)arrayList->elementArray->data + (arrayList->elementTypeSize * (--arrayList->size));
   }
}

static void instanceRemove(ArrayList* arrayList, int index)
{
   if ((index >= 0) && (index < arrayList->size))
   {
      arrayList->size--;

      if (index != arrayList->size)
      {
         void *to = (char *)arrayList->elementArray->data + arrayList->elementTypeSize * index;
         void *from = (char *)to + arrayList->elementTypeSize;

        memmove(to, from, arrayList->elementTypeSize * (arrayList->size - index));
      }        
   }
}

static void instanceRemoveRange(ArrayList* arrayList, int fromIndex, int toIndex)
{
   int num, lastIndex;

   if ((fromIndex >= 0 && (fromIndex < arrayList->size)) &&
       (toIndex >= 0 && (toIndex < arrayList->size)))
   {
      if (toIndex >= fromIndex)
      {
         num = toIndex - fromIndex + 1;
         lastIndex = arrayList->size - 1;

         arrayList->size -= num;

         if (toIndex != fromIndex)
         {
            void *to = (char *)arrayList->elementArray->data + arrayList->elementTypeSize * fromIndex;
            void *from = (char *)to + arrayList->elementTypeSize * num;

            memmove(to, from, arrayList->elementTypeSize * (lastIndex - toIndex));
         }
      }
   }
}

static void instanceRemoveByLast(ArrayList* arrayList, int index)
{
   instanceRemoveRange(arrayList, index, arrayList->size - 1);
}

static void instanceClear(ArrayList* arrayList)
{
   arrayList->size = 0;
}

static void instanceRelease(ArrayList** arrayList)
{
   freeArrayList(arrayList);
}

ArrayList* newArrayList(int elementTypeSize)
{
   ArrayList *outArrayList          = (ArrayList *)malloc(sizeof(ArrayList));

   outArrayList->fptrSize           = instanceSize;
   outArrayList->fptrGet            = instanceGet;

   outArrayList->fptrAdd            = instanceAdd;
   outArrayList->fptrAddArray       = instanceAddArray;
   outArrayList->fptrInsert         = instanceInsert;

   outArrayList->fptrPop            = instancePop;
   outArrayList->fptrRemove         = instanceRemove;
   outArrayList->fptrRemoveRange    = instanceRemoveRange;
   outArrayList->fptrRemoveByLast   = instanceRemoveByLast;

   outArrayList->fptrClear          = instanceClear;
   outArrayList->fptrRelease        = instanceRelease;

   initArrayList(elementTypeSize, outArrayList);

   return outArrayList;
}

void freeArrayList(ArrayList** const arrayList)
{
   if (NULL != *arrayList)
   {
      if ((*arrayList)->elementArray->data != NULL)
      {
         free((*arrayList)->elementArray->data);
         (*arrayList)->elementArray->data = NULL;
      }

      free(*arrayList);
      *arrayList = NULL;
   }
}
 
