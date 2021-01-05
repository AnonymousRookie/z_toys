#ifndef Z_NET_SRC_TIME_STAMP_H
#define Z_NET_SRC_TIME_STAMP_H

#include <map>
#include <vector>
#include <stdint.h>
#include "defines.h"

NAMESPACE_BEGIN(z_net)

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);

    ~Timestamp();

    static Timestamp now();

private:
    int64_t microSecondsSinceEpoch_;
};

NAMESPACE_END(z_net)

#endif  // Z_NET_SRC_TIME_STAMP_H