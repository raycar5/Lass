#pragma once
#include <stdlib.h>

enum LASSType { LASSLong = 1, LASSSymbol = 2, LASSList = 3 };
typedef struct LASSValue {
  enum LASSType Type;
} * LASSValueRef;

// LASSLong
typedef struct LASSLong {
  struct LASSValue Base;
  long Value;
} * LASSLongRef;
LASSLongRef LASSLongCreate(long Value);
char *LASSLongPrint(LASSLongRef Val);

// LASSSymbol
typedef struct LASSSymbol {
  struct LASSValue Base;
  const char *Name;
} * LASSSymbolRef;
LASSSymbolRef LASSSymbolCreate(const char *Name);
char *LASSSymbolPrint(LASSSymbolRef Val);

// LASSList
typedef struct LASSListNode {
  LASSValueRef Value;
  struct LASSListNode *Next;
} * LASSListNodeRef;
LASSListNodeRef LASSListNodeCreate(LASSValueRef Value, LASSListNodeRef Next);

typedef struct LASSList {
  struct LASSValue Base;
  LASSListNodeRef Front;
  LASSListNodeRef Back;
  size_t Count;
} * LASSListRef;
LASSListRef LASSListCreate();
void LASSListAdd(LASSListRef List, LASSValueRef Value);
char *LASSListPrint(LASSListRef Val);

// General functions
char *LASSPrintValueToString(LASSValueRef Val);
