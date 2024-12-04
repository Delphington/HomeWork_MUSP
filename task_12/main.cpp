#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>


class CoffeeShop {
private:
    size_t maxCustomers;
    size_t customersServed;
    std::queue<int> waiting_customers;
    std::mutex mutex_;
    std::condition_variable condition_;

public:
    CoffeeShop(size_t max_customers) : maxCustomers(max_customers), customersServed(0) {}

    // Метод для входа клиента в кофейню
    void enter(int customer_id) {
        std::unique_lock<std::mutex> lock(mutex_); // Блокируем мьютекс для безопасного доступа к общим данным
        // Проверяем, есть ли свободные места
        if (waiting_customers.size() < maxCustomers) {
            waiting_customers.push(customer_id); // Добавляем клиента в очередь ожидания
            std::cout << "Customer " << customer_id << " took a seat. Waiting customers: " << waiting_customers.size() << std::endl;
            condition_.notify_one(); // Уведомляем баристу, что есть клиент
        } else {
            // Если мест нет, клиент покидает кофейню
            std::cout << "Customer " << customer_id << " left the shop (no seats available)." << std::endl;
        }
    }

    // Метод, который обслуживает клиентов
    void serve() {
        while (true) { // Бесконечный цикл для постоянного обслуживания клиентов
            int customer_id;
            {
                std::unique_lock<std::mutex> lock(mutex_); // Блокируем мьютекс для безопасного доступа к очереди клиентов
                // Ожидаем, пока не появится клиент в очереди
                condition_.wait(lock, [this] { return !waiting_customers.empty(); });
                customer_id = waiting_customers.front(); // Берем клиента из начала очереди
                waiting_customers.pop(); // Убираем клиента из очереди
            }
            // Симуляция обслуживания кофе
            std::cout << "Barista is serving coffee to customer " << customer_id << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Время, необходимое для обслуживания кофе
            customersServed++; // Увеличиваем счетчик обслуженных клиентов
            std::cout << "Customer " << customer_id << " has been served." << std::endl;
        }
    }


};

// Функция потока клиента
void customer_thread(CoffeeShop& shop, int id) {
    // Клиент ждет случайное время перед входом в кофейню
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 901 + 100)); // Случайное время ожидания между 100 и 1000 мс
    shop.enter(id); // Клиент пытается войти в кофейню
}

int main() {
    const int num_customers = 20;
    const int max_seats = 5;

    CoffeeShop shop(max_seats);

    // Запускаем поток баристы
    std::thread barista(&CoffeeShop::serve, &shop);

    // Запускаем потоки клиентов
    std::vector<std::thread> customers;
    for (int i = 0; i < num_customers; ++i) {
        customers.emplace_back(customer_thread, std::ref(shop), i + 1); // Создаем поток для каждого клиента
    }

    // Дожидаемся завершения всех потоков клиентов
    for (auto& customer : customers) {
        customer.join();
    }

    // Опционально, можем остановить поток баристы после обслуживания всех клиентов
    barista.detach(); // Отсоединяем поток баристы, чтобы он продолжал работать независимо

    return 0; // Завершение программы
}
