#include "TimeMeter.h"
#ifdef _WIN32
#include "TimeMeter_win.cpp"
#else
#include "TimeMeter_lin.cpp"
#endif


TimeMeter::TimeMeter(unsigned count): _pimpl(new TimeMeterOS(count)) {}

double TimeMeter::setTimeStamp(unsigned num)
{
    return _pimpl->setTimeStamp(num);
}
double TimeMeter::getSTimeStamp(unsigned num) const
{
    return _pimpl->getSTimeStamp(num);
}
int64_t TimeMeter::getMSTimeStamp(unsigned num) const
{
    return _pimpl->getMSTimeStamp(num);
}
double TimeMeter::getSDiff(unsigned first, unsigned second) const
{
    return _pimpl->getSDiff(first, second);
}
int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const
{
    return _pimpl->getMSDiff(first, second);
}
bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) const
{
    return _pimpl->isLess(first, second, expected);
}
bool TimeMeter::isLess(unsigned num, int64_t expected) const
{
    return _pimpl->isLess(num, expected);
}
