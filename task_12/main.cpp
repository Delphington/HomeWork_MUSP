#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;

class CoffeeShop {
private:
    queue<int> clientQueue;
    condition_variable waitGroup;

    mutex myMutex;
    volatile bool isWorkCoffee;
    int countSeat;

    thread baristaThread;
    thread clientThread;
public:
    CoffeeShop(int countSeat) : isWorkCoffee(true), countSeat(countSeat) {}

    // Деструктор класса CoffeeShop. Устанавливает флаг isOpen в false, уведомляет баристу о закрытии и ждет завершения потоков.
    ~CoffeeShop() {
        isWorkCoffee = false;
        waitGroup.notify_one(); // Сигнализируем баристе о закрытии
        if (baristaThread.joinable()) baristaThread.join();
        if (clientThread.joinable()) clientThread.join();
    }

    // Запускает потоки бариста и генератора клиентов.
    void start() {
        baristaThread = thread(&CoffeeShop::baristaWork, this);
        clientThread = thread(&CoffeeShop::generateClient, this);
    }

private:
    void baristaWork() {
        while (isWorkCoffee || !clientQueue.empty()) {
            unique_lock<mutex> lock(myMutex); // Блокируем мьютекс перед доступом к очереди.

            // Блокируем, ждем нового клиента
            waitGroup.wait(lock, [this] {
                return !clientQueue.empty() || !isWorkCoffee; }
                );

            if (!clientQueue.empty()) {
                int consimer = clientQueue.front();
                clientQueue.pop();
                lock.unlock();
                cout << "Бариста варит кофе для клиента : " << consimer << endl;
                this_thread::sleep_for(chrono::seconds(3)); // Имитация приготовления кофе.
                cout << "Бариста закончил с клиентом : " << consimer << std::endl;
            } else if (!isWorkCoffee) {
                return;
            }
        }
        cout << "Бариста купил себе свободу" << endl;
    }

    // Функция, имитирующая генерацию клиентов.
    void generateClient() {
        int consimer = 1;
        default_random_engine dre;
        minstd_rand gen(dre());
        uniform_int_distribution<> ourRandom(500, 3000); // Распределение для задержки (500-2000 мс).

        while (isWorkCoffee) {
            this_thread::sleep_for(chrono::milliseconds(ourRandom(gen))); // Случайная задержка перед появлением клиента.

            lock_guard<mutex> lock(myMutex);
            if (clientQueue.size() < countSeat) {
                clientQueue.push(consimer++);
                cout << "Клиент : " << consimer - 1 << " занял место. Ждуны: " << clientQueue.size() << endl;
                waitGroup.notify_one();
            } else {
                cout << "Клиент : " << consimer << " ушел. Все стулья заняты" << endl;
            }
        }
    }
};

int main() {
    // Устанавливаем кодировку консоли для корректного отображения кириллицы на Windows.
    SetConsoleOutputCP(CP_UTF8);

    CoffeeShop shop(5); // Создаем кофейню с 5 стульями
    shop.start();
    this_thread::sleep_for(chrono::seconds(30)); // Работа кофейни 20 секунд
    return 0;
}
