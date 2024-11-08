#include "TimeMeter_win.h"


TimeMeterOS::TimeMeterOS(unsigned count)
{
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_ts);
    _stamps.resize(count);
    _count = count;
}

double TimeMeterOS::getSDiff(unsigned first, unsigned second) const
{
    if (first >= _count || second >= _count)
        throw std::out_of_range("Stamp index out of range\n");
    return _getSDiff(_stamps[first], _stamps[second]);
}

int64_t TimeMeterOS::getMSDiff(unsigned first, unsigned second) const
{
    return static_cast<int64_t>(_getSDiff(_stamps[first],
                                          _stamps[second]) * 1000);
}

double TimeMeterOS::setTimeStamp(unsigned num)
{
    if (num >= _count)
        throw std::out_of_range("Stamp index out of range\n");
    LARGE_INTEGER ts;
    QueryPerformanceCounter(&ts);
    _stamps[num] = ts;
    return _getSDiff(_ts, ts);
}

double TimeMeterOS::getSTimeStamp(unsigned num) const
{
    if (num >= _count)
        throw std::out_of_range("Stamp index out of range\n");
    return _getSDiff(_ts, _stamps[num]);
}

int64_t TimeMeterOS::getMSTimeStamp(unsigned num) const
{
    return static_cast<int64_t>(getSTimeStamp(num) * 1000);
}

bool TimeMeterOS::isLess(unsigned first, unsigned second, int64_t expected) const
{
    return (getMSDiff(first, second) < expected);
}

bool TimeMeterOS::isLess(unsigned num, int64_t expected) const
{
    return (getMSTimeStamp(num) < expected);
}

