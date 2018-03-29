#pragma once

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif
typedef struct LASSOpaqueParser *LASSParserRef;
extern LASSParserRef LASSTokenize(const char *Line);
extern void LASSParserDestroy(LASSParserRef Parser);
extern const char *LASSParserPeek(LASSParserRef Parser);
extern const char *LASSParserNext(LASSParserRef Parser);
extern bool LASSParserIsInt(const char *pred);
#ifdef __cplusplus
}
#endif
