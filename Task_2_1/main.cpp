#include <iostream>
#include "TimeMeter.h"
#include "TimeMeterImplemetation.h"

int main()
{
    TimeMeter time(5);
    std::cout << std::fixed << "time after programm start: " << time.setTimeStamp(0) << std::endl;
    std::cin.get();
    std::cout << "time after start: " << time.setTimeStamp(1) << std::endl;
    std::cout << "first stamp(milliseconds, seconds): " << time.getMSTimeStamp(0) << ";" << time.getSTimeStamp(0) << std::endl;
    std::cout << "second stamp(milliseconds, seconds): " << time.getMSTimeStamp(1) << ";" << time.getSTimeStamp(1) << std::endl;
    std::cout << "time after start: " << time.setTimeStamp(2) << std::endl;
    std::cout << "difference first and second(seconds, microseconds): " << time.getSDiff(0, 1) << ";" << time.getMSDiff(0, 1) << std::endl;
    std::cout << "difference second and third(seconds, microseconds): " << time.getSDiff(1, 2) << ";" << time.getMSDiff(1, 2) << std::endl;
    std::cout << "if second less then 3 seconds: " << time.isLess(1, 3000) << std::endl;
    std::cout << "if diff second and third less then 3 seconds: " << time.isLess(1, 2, 3000) << std::endl;
    return 0;
}