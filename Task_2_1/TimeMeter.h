#pragma once

#include <iostream>
#include <memory>

class TimeMeterImplemetation;

class TimeMeter {
public:
    //запоминает время начала отсчета и необходимое количество временных меток
    TimeMeter(unsigned count);

    //установка временной метки (от начала времени отсчета)
    double setTimeStamp(unsigned num);

    //Получение времени метки в секундах и миллисекундах
    double getSTimeStamp(unsigned num) const;
    int64_t getMSTimeStamp(unsigned num) const;

    //Получение разницы между метками в секундах и миллисекундах
    double getSDiff(unsigned first, unsigned second) const;
    int64_t getMSDiff(unsigned first, unsigned second) const;

    //Проверка, не превосходит ли ожидаемого значения (в секундах и миллисекундах)
    bool isLess(unsigned first, unsigned second, int64_t expected) const;
    bool isLess(unsigned num, int64_t expected) const;

    ~TimeMeter() = default;
private:
    std::shared_ptr <TimeMeterImplemetation> _pimpl = nullptr;
};
