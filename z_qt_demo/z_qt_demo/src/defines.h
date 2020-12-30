#pragma once

#include <assert.h>

#define RET_OK 0
#define RET_ERROR -1

#define Z_CHECK(x) if (!(x)) { return; }
#define Z_CHECK_RETURN(x, v) if (!(x)) { return (v); }
#define Z_CHECK_CONTINUE(x) if (!(x)) { continue; }
#define Z_CHECK_BREAK(x) if (!(x)) { break; }

#define Z_CHECK_EQUAL_ASSERT(x, v) assert((v) == (x));
#define Z_CHECK_ASSERT(x) assert((x));

#define NAMESPACE_BEGIN(n) namespace n {
#define NAMESPACE_END(n)   }
