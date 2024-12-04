#pragma once

#include "TimeMeterImplemetation.h"
#include <windows.h>
#include <vector>


class TimeMeterOS : public TimeMeterImplemetation {
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
    LARGE_INTEGER timeStart; // начало отсчета
    LARGE_INTEGER frequency; // частота
    std::vector<LARGE_INTEGER> arrStamps; // для хранения временный меток
    unsigned countStamps = 0; // кол-во меток

    //разница между метками в секундах
    double _getSDiff(const LARGE_INTEGER &first, const LARGE_INTEGER &second) const {
        return static_cast<double>(second.QuadPart - first.QuadPart) / frequency.QuadPart;
    }
};

typedef TimeMeterOS TimeMetrOS;
