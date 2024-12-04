#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <functional>
#include <variant>
#include <valarray>

using namespace std;
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};


class Logger {
private:
    LogLevel levelCurr;
    ostream &output;

    static string getLogString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
        }
    }

public:
    Logger(ostream &out = cout, LogLevel logLevel = LogLevel::DEBUG) : output(out), levelCurr(logLevel) {}

    // Метод для логирования сообщения
    template<typename... Args>
    //произвольный уровень параметров
    void log(LogLevel level, Args &&... args) {
        ostringstream oss;
        oss << "[" << getLogString(level) << "] ";
        (oss << ... << forward<Args>(args)); //позволяет все элементы передать из args
        output << oss.str() << endl;
    }

    // Метод для измерения времени выполнения функции
    template<typename Func>
    //lamda
    void log_time(LogLevel level, const std::string &message, Func &&func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        //продолжительность
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        log(level, message, " (Execution time: ", duration, " ms)");
    }

    // Метод для обработки исключений
    template<typename Func>
    void log_exception(Func &&func) {
        try {
            func();
        } catch (const std::exception &e) {
            log(LogLevel::ERROR, "Error occurred Exception caught: File not found", e.what());
        } catch (...) {
            log(LogLevel::ERROR, "Unknown exception caught.");
        }
    }


};

class Srv {
private:
    int n = 0;
    int level = 0;

    LogLevel levelCurr;

    void levelInit() {
        switch (level) {
            case 1:
                levelCurr = LogLevel::DEBUG;
                break;
            case 2:
                levelCurr = LogLevel::WARNING;
                break;
            case 3:
                levelCurr = LogLevel::ERROR;
                break;
            case 4:
                levelCurr = LogLevel::CRITICAL;
                break;

        }
    }

    void inputInfo() {
        cout << "Enter the number: " << endl;
        cout << "[1] Write the file" << endl;
        cout << "[2] Write the console" << endl;
        cin >> n;
        if (n != 1 && n != 2) {
            throw std::runtime_error("not correct");
        }


        cout << "Enter the number: " << endl;
        cout << "[1] DEBUG" << endl;
        cout << "[2] WARNING" << endl;
        cout << "[3] ERROR" << endl;
        cout << "[4] CRITICAL" << endl;
        cin >> level;
        if (level < 1 || level > 4) {
            throw std::runtime_error("not correct");
        }
        levelInit();

    }

    void parsToFile() {
        // Логгер для вывода в файл
        std::ofstream fileLogger("res/text.txt");

        if (!fileLogger.is_open()) {
            std::cerr << "Failed to open log file!" << std::endl;
            throw std::runtime_error("not found");
        }
        // Логгер для вывода в консоль
        Logger consoleLogger(fileLogger);

        // Логируем обычное сообщение
        consoleLogger.log(levelCurr, "Calculation started with values ", 42, " and ", 58);

        // Логируем выполнение функции с замером времени
        consoleLogger.log_time(levelCurr, "Calculated sum", []() {
            int sum = 42 + 58;
        });

        // Логируем выполнение функции с обработкой исключения
        consoleLogger.log_exception([]() {
            throw std::runtime_error("File not found");
        });

    }

    void parsToConsole() {
        Logger consoleLogger;

        // Логируем обычное сообщение
        consoleLogger.log(levelCurr, "Calculation started with values ", 42, " and ", 58);

        // Логируем выполнение функции с замером времени
        consoleLogger.log_time(levelCurr, "Calculated sum", []() {
            int sum = 500000 + 313131;
        });

        // Логируем выполнение функции с обработкой исключения
        consoleLogger.log_exception([]() {
            throw std::runtime_error("File not found");
        });
    }

public:
    void start() {
        inputInfo();
        parseInfo();
    }

    void parseInfo() {
        if (n == 1) {
            parsToFile();
        } else {
            parsToConsole();
        }
    }
};

int main() {
    Srv srv;
    srv.start();
    return 0;
}

