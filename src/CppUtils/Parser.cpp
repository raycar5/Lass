#include "Parser.h"
#include <regex>

using namespace std;
struct LASSOpaqueParser {
  LASSOpaqueParser(const char *Line) {
    static const regex TokenRegex(
        R"regex([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))regex",
        regex_constants::ECMAScript);
    const auto Len = strlen(Line);
    RegexIterator = cregex_iterator(Line, Line + Len, TokenRegex);
  }
  auto peek() const { return (*RegexIterator)[1].str(); }
  auto next() { return (*RegexIterator++)[1].str(); }

private:
  cregex_iterator RegexIterator;
};
LASSParserRef LASSTokenize(const char *Line) {
  return new LASSOpaqueParser(Line);
}
void LASSParserDestroy(LASSParserRef Parser) { delete Parser; }
const char *LASSParserPeek(LASSParserRef Parser) {
  auto RetString = Parser->peek();
  auto Size = RetString.size();
  auto *Ret = static_cast<char *>(malloc(sizeof(char) * Size + 1));
  strcpy(Ret, RetString.c_str());
  return Ret;
}
const char *LASSParserNext(LASSParserRef Parser) {
  auto RetString = Parser->next();
  auto Size = RetString.size();
  auto *Ret = static_cast<char *>(malloc(sizeof(char) * Size + 1));
  strcpy(Ret, RetString.c_str());
  return Ret;
}
bool LASSParserIsInt(const char *pred) {
  static const regex IntRegex(R"regex(^-?[0-9]+$)regex");
  return regex_search(pred, IntRegex);
}
