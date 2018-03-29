#include "types.h"
#include <stdio.h>
#include <string.h>

// TODO refactor to adhere to LLVM coding standards
// https://llvm.org/docs/CodingStandards.html

LASSLongRef LASSLongCreate(long value) {
  LASSLongRef ref = (LASSLongRef)malloc(sizeof(struct LASSLong));
  ref->Base.Type = LASSLong;
  ref->Value = value;
  return ref;
}
char *LASSLongPrint(LASSLongRef Val) {
  char *string = (char *)malloc(sizeof(char) * 200);
  sprintf(string, "Long:%i", Val->Value);
  return string;
};

LASSSymbolRef LASSSymbolCreate(const char *name) {
  LASSSymbolRef ref = (LASSSymbolRef)malloc(sizeof(struct LASSSymbol));
  ref->Base.Type = LASSSymbol;
  ref->Name = name;
  return ref;
}
char *LASSSymbolPrint(LASSSymbolRef Val) {
  char *string = (char *)malloc(sizeof(char) * 200);
  sprintf(string, "Symbol:%s", Val->Name);
  return string;
}

LASSListNodeRef LASSListNodeCreate(LASSValueRef value, LASSListNodeRef next) {
  LASSListNodeRef ref = (LASSListNodeRef)malloc(sizeof(struct LASSListNode));
  ref->Value = value;
  ref->Next = next;
  return ref;
}
LASSListRef LASSListCreate() {
  LASSListRef ref = (LASSListRef)malloc(sizeof(struct LASSList));
  ref->Base.Type = LASSList;
  ref->Front = NULL;
  ref->Back = NULL;
  ref->Count = 0;
  return ref;
}
void LASSListAdd(LASSListRef List, LASSValueRef Value) {
  LASSListNodeRef Node = LASSListNodeCreate(Value, NULL);
  if (List->Back) {
    List->Back->Next = Node;
  } else {
    List->Front = Node;
  }
  List->Back = Node;
  List->Count++;
}
char *LASSListPrint(LASSListRef Val) {
  char *string = (char *)malloc(sizeof(char) * 10 + 200 * Val->Count);
  *string = '\0';
  strcat(string, "List:(");

  LASSListNodeRef node = Val->Front;
  while (node) {
    char *temp = LASSPrintValueToString(node->Value);
    strcat(string, temp);
    free(temp);
    node = node->Next;
    if (node)
      strcat(string, ", ");
  }

  strcat(string, ")");
  return string;
}

char *LASSPrintValueToString(LASSValueRef Val) {
  if (Val) {
    switch (Val->Type) {
    case LASSLong:
      return LASSLongPrint((LASSLongRef)Val);
    case LASSSymbol:
      return LASSSymbolPrint((LASSSymbolRef)Val);
    case LASSList:
      return LASSListPrint((LASSListRef)Val);
    default:
      return "unknown";
    }
  } else {
    return NULL;
  }
}
