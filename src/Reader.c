#include "reader.h"
#include "Parser.h"
#include <string.h>

static LASSValueRef LassReadForm(LASSParserRef Parser);
static LASSValueRef LassReadAtom(LASSParserRef Parser) {
  const char *Token = LASSParserNext(Parser);
  if (LASSParserIsInt(Token)) {
    LASSValueRef Ret = (LASSValueRef)LASSLongCreate(strtol(Token, NULL, 10));
    free((void *)Token);
    return Ret;
  } else {
    return (LASSValueRef)LASSSymbolCreate(Token);
  }
}
static LASSListRef LassReadList(LASSParserRef Parser) {
  free((void *)LASSParserNext(Parser));
  LASSListRef List = LASSListCreate();

  while (true) {
    const char *Token = LASSParserPeek(Parser);
    if (strcmp(Token, ")") == 0) {
      free((void *)LASSParserNext(Parser));
      free((void *)Token);
      return List;
    } else {
      LASSListAdd(List, LassReadForm(Parser));
    }
    free((void *)Token);
  }
}

static LASSValueRef LassReadForm(LASSParserRef Parser) {
  const char *Token = LASSParserPeek(Parser);
  if (strcmp(Token, "(") == 0) {
    return (LASSValueRef)LassReadList(Parser);
  } else if (strcmp(Token, ")") == 0) {
    return NULL;
  } else {
    return LassReadAtom(Parser);
  }

  free((void *)Token);
}
LASSValueRef LASSReadString(const char *String) {
  const LASSParserRef Parser = LASSTokenize(String);
  const LASSValueRef Ast = LassReadForm(Parser);
  LASSParserDestroy(Parser);
  return Ast;
}
