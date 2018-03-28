#include "Types.h"
#include "llvm/IR/Value.h"
#include <iostream>
#include <regex>

using namespace std;
using namespace lass;
using namespace llvm;
class Parser {
public:
  Parser(cregex_iterator iter) : iter(iter) {}
  auto peek() { return (*iter)[1]; }
  auto next() { return (*iter++)[1]; }

private:
  cregex_iterator iter;
};

unique_ptr<LassValue> read_form(Parser *iter);
Parser tokenize(const char *str) {
  static const regex token_regex(
      R"regex([\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"|;.*|[^\s\[\]{}('"`,;)]*))regex",
      regex_constants::ECMAScript);
  const auto len = strlen(str);
  return Parser(cregex_iterator(str, str + len, token_regex));
}

unique_ptr<LassValue> read_atom(Parser *iter) {
  static const regex int_regex(R"regex(^-?[0-9]+$)regex");
  auto token = iter->next();
  if (std::regex_search(string(token), int_regex)) {
    return std::make_unique<LassLong>(stol(token));
  } else {
    return std::make_unique<LassSymbol>(token);
  }
}
unique_ptr<LassValue> read_list(Parser *iter) {
  iter->next();
  auto list = std::make_unique<LassList>();
  while (true) {
    auto token = iter->peek();
    if (token == ")") {
      ++iter;
      return list;
    } else {
      list->add(std::move(read_form(iter)));
    }
  }
}
unique_ptr<LassValue> read_form(Parser *iter) {
  auto token = iter->peek();
  if (token == ")") {
    return nullptr;
  } else if (token == "(") {
    return read_list(iter);
  } else {
    return read_atom(iter);
  }
}
int main() {
  while (true) {
    string s;
    getline(cin, s);
    auto iter = tokenize(s.c_str());
    cout << read_form(&iter)->print(true) << "\n";
  }
  return 0;
}
