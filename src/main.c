#include "Parser.h"
#include "Types.h"
#include "reader.h"
#include <stdio.h>

int main() {
  // printf() displays the string inside quotation
  char stringo[1000];

  while (true) {
    fgets(stringo, 1000, stdin);
    printf("%s\n", LASSPrintValueToString(LASSReadString(stringo)));
  }
  getchar();
  return 0;
}
