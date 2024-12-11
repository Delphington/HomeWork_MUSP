#include <iostream>
#include "TimeMeter.h"
#include "TimeMeterImplemetation.h"
#include <windows.h>
#include <functional>
#include <cmath>


using namespace std;


class Srv {
public:
    static void test() {
        TimeMeter time(5);
        cout << std::fixed << "Время после запуска программы: " << time.setTimeStamp(0) << std::endl;
        cin.get();
        cout << "Время после начала: " << time.setTimeStamp(1) << endl;
        cout << "Первая отметка (миллисекунды, секунды): " << time.getMSTimeStamp(0) << "; " << time.getSTimeStamp(0)
             << endl;
        cout << "Вторая отметка (миллисекунды, секунды): " << time.getMSTimeStamp(1) << "; " << time.getSTimeStamp(1)
             << endl;
        cout << "Время после начала:" << time.setTimeStamp(2) << endl;
        cout << "Разница первого и второго (секунды, микросекунды): " << time.getSDiff(0, 1) << "; "
             << time.getMSDiff(0, 1) << endl;
        cout << "Разница секунд и третьих(секунды, микросекунды): " << time.getSDiff(1, 2) << "; "
             << time.getMSDiff(1, 2) << endl;
        cout << "Если секунда меньше 3 секунд:" << time.isLess(1, 3000) << endl;
        cout << "Если разница между вторым и третьим менее 3 секунд: " << time.isLess(1, 2, 3000) << endl;
    }

    static int measureTime(function<void(int&, int&)> f, int& result1) {
        TimeMeter meter(1);
        f(result1, result1); // Вызываем функцию
        meter.setTimeStamp(0);
        return meter.getMSTimeStamp(0);
    }

    static void sleeper(int x, int y, int& result) {
        result++;
        Sleep(101 * x * y);
    }
};


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int c1 = 1, c2 = 3;
    int result1 = 0, result2 = 0;

    cout << "time 1: "
         << Srv::measureTime([c1, c2](int& res1, int&) { Srv::sleeper(c1, c2, res1); }, result1)
         << endl;

    cout << "time 2: "
         << Srv::measureTime(bind((Srv::sleeper), c1, c2, ref(result2)), result2)
         << endl;

    return 0;
}

/**
   g++ main.cpp TimeMeter.cpp -o capy
   ./capy
*/