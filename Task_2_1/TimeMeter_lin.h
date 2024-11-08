#pragma once
#include "TimeMeterImplemetation.h"
#include <vector>
#include <cstdint>
#include <ctime>



class TimeMeterOS : public TimeMeterImplemetation
{
public:
    TimeMeterOS(unsigned count);
    double setTimeStamp(unsigned num) override;
    double getSTimeStamp(unsigned num) const override;
    int64_t getMSTimeStamp(unsigned num) const override;
    double getSDiff(unsigned first, unsigned second) const override;
    int64_t getMSDiff(unsigned first, unsigned second) const override;
    bool isLess(unsigned first, unsigned second, int64_t expected) const override;
    bool isLess(unsigned num, int64_t expected) const override;
private:
    std::timespec _ts; //< начало отсчета
    std::vector<std::timespec> _stamps; //< вектор меток;
    unsigned _count = 0; //< кол-во меток
    //! разница между метками в секундах
    double _getSDiff(const std::timespec& first, const std::timespec& second) const
    {
        return (second.tv_sec - first.tv_sec) + 
               (second.tv_nsec - first.tv_nsec) / 1e9;
    }
};
