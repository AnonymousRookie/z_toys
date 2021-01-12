#ifndef Z_DATA_STRUCT_DEFINES_H
#define Z_DATA_STRUCT_DEFINES_H

#include <stdint.h>
#include <assert.h>

#define Z_CHECK(p) if (!(p)) return;
#define Z_CHECK_RETURN(p, r) if (!(p)) return r;
#define Z_CHECK_CONTINUE(p) if (!(p)) continue;
#define Z_CHECK_BREAK(p) if (!(p)) break;

#define NAMESPACE_BEGIN(n) namespace n {
#define NAMESPACE_END(n)   }


#endif  // Z_DATA_STRUCT_DEFINES_H