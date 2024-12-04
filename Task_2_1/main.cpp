#include <iostream>
#include "TimeMeter.h"
#include "TimeMeterImplemetation.h"
#include <windows.h>

using namespace std;

/**
   g++ main.cpp TimeMeter.cpp -o capy
   ./capy
*/

int main(){
    SetConsoleOutputCP(CP_UTF8);
    TimeMeter time(5);
    cout << std::fixed << "Время после запуска программы: " << time.setTimeStamp(0) << std::endl;
    cin.get();
    cout << "Время после начала: " << time.setTimeStamp(1) << endl;
    cout << "Первая отметка (миллисекунды, секунды): " << time.getMSTimeStamp(0) << "; " << time.getSTimeStamp(0) << endl;
    cout << "Вторая отметка (миллисекунды, секунды): " << time.getMSTimeStamp(1) << "; " << time.getSTimeStamp(1) <<endl;
    cout << "Время после начала:" << time.setTimeStamp(2) <<endl;
    cout << "Разница первого и второго (секунды, микросекунды): " << time.getSDiff(0, 1) << "; " << time.getMSDiff(0, 1) << endl;
    cout << "Разница секунд и третьих(секунды, микросекунды): " << time.getSDiff(1, 2) << "; " << time.getMSDiff(1, 2) << endl;
    cout << "Если секунда меньше 3 секунд:" << time.isLess(1, 3000) << endl;
    cout << "Если разница между вторым и третьим менее 3 секунд: " << time.isLess(1, 2, 3000) << endl;
    return 0;
}