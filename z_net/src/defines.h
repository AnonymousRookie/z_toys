#ifndef Z_NET_SRC_DEFINES_H
#define Z_NET_SRC_DEFINES_H

#include <stdint.h>
#include <string.h>
#include <string>
#include <assert.h>
#include "logger.h"

#define Z_CHECK(p) if (!(p)) return;
#define Z_CHECK_RETURN(p, r) if (!(p)) return r;
#define Z_CHECK_CONTINUE(p) if (!(p)) continue;
#define Z_CHECK_BREAK(p) if (!(p)) break;

#define NAMESPACE_BEGIN(n) namespace n {
#define NAMESPACE_END(n)   }


#endif  // Z_NET_SRC_DEFINES_H