#include "TimeMeter_win.h"
//API

TimeMeterOS::TimeMeterOS(unsigned count) {
    QueryPerformanceFrequency(&frequency); //частота таймера
    QueryPerformanceCounter(&timeStart); //текущее значение счетчика
    arrStamps.resize(count);
    countStamps = count;
}

// Получение разницы между метками в секундах и миллисекундах
double TimeMeterOS::getSDiff(unsigned first, unsigned second) const {
    if (first >= countStamps || second >= countStamps)
        throw std::out_of_range("Stamp index out of range\n");
    return _getSDiff(arrStamps[first], arrStamps[second]);
}

// Получение разницы между метками в секундах и миллисекундах
int64_t TimeMeterOS::getMSDiff(unsigned first, unsigned second) const {
    return static_cast<int64_t>(_getSDiff(arrStamps[first],arrStamps[second]) * 1000);
}

// установка временной метки (от начала времени отсчета
double TimeMeterOS::setTimeStamp(unsigned num) {// индекс
    if (num >= countStamps)
        throw std::out_of_range("Stamp index out of range\n");
    LARGE_INTEGER ts;
    QueryPerformanceCounter(&ts); //текущее значение
    arrStamps[num] = ts;
    return _getSDiff(ts, ts); //0
}

// Получение времени метки в секундах и миллисекундах
double TimeMeterOS::getSTimeStamp(unsigned num) const {
    if (num >= countStamps)
        throw std::out_of_range("Stamp index out of range\n");
    return _getSDiff(timeStart, arrStamps[num]);
}

// Получение времени метки в секундах и миллисекундах
int64_t TimeMeterOS::getMSTimeStamp(unsigned num) const {
    return static_cast<int64_t>(getSTimeStamp(num) * 1000);
}

// Проверка, не превосходит ли ожидаемого значения (в секундах и миллисекундах)
bool TimeMeterOS::isLess(unsigned first, unsigned second, int64_t expected) const {
    return (getMSDiff(first, second) < expected);
}

// Проверка, не превосходит ли ожидаемого значения (в секундах и миллисекундах)
bool TimeMeterOS::isLess(unsigned num, int64_t expected) const {
    return (getMSTimeStamp(num) < expected);
}

