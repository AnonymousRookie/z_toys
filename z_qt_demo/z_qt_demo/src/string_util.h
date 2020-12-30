#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <QString>
#include "defines.h"

NAMESPACE_BEGIN(z)
NAMESPACE_BEGIN(utils)

inline QString str2qstr(const std::string& str)
{
    return QString::fromLocal8Bit(str.data());
}

inline std::string qStr2Str(const QString& qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}

NAMESPACE_END(utils)
NAMESPACE_END(z)
