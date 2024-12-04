#pragma once
#include <iostream>
#include <cstdint>


class TimeMeterImplemetation{
public:
    // установка временной метки (от начала времени отсчета
    virtual double setTimeStamp(unsigned num) = 0;
    // Получение времени метки в секундах и миллисекундах
    virtual double getSTimeStamp(unsigned num) const = 0;
    virtual int64_t getMSTimeStamp(unsigned num) const = 0;
    // Получение разницы между метками в секундах и миллисекундах
    virtual double getSDiff(unsigned first, unsigned second) const = 0;
    virtual int64_t getMSDiff(unsigned first, unsigned second) const = 0;
    // Проверка, не превосходит ли ожидаемого значения (в секундах и миллисекундах)
    virtual bool isLess(unsigned first, unsigned second, int64_t expected) const = 0;
    virtual bool isLess(unsigned num, int64_t expected) const = 0;
    virtual ~TimeMeterImplemetation() = default;
};
