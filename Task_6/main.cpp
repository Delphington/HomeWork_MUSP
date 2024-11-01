#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

class Srv {
private:
    string path;
    int n = 0, a = 0, b = 0;
    vector<int> arr;

public:
    Srv(const string &path) {
        this->path = path;
    }

    void inputInfo() {
        ifstream inputFile(path);

        if (!inputFile) {
            cerr << "Cannot open file. Cannot read." << endl;
            return;
        }
        inputFile >> n >> a >> b;
        int number;
        while (inputFile >> number) {
            arr.push_back(number);
        }
        inputFile.close();
    }

    void solve() {

        cout << "[a, b] = " << "[" << a << ", " << b << "]\n";

        //Создаем итератор, который и выводит
        cout << "Input: ";
        copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        // удаление элементов
        auto range = remove_if(arr.begin(), arr.end(), [this](int x) {
                                   return x < a || x > b;
                               }
        );
        arr.erase(range, arr.end());

        cout << "After remove: ";
        copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        // Исключить из полученного массива
        // первый четный элемент, следующий за максимальным.
        if (!arr.empty()) {
            auto maxElement = max_element(arr.begin(), arr.end());
            //находим след элемент после макс
            auto findAfterMax = find_if(maxElement + 1, arr.end(), [](int x) { return x % 2 == 0; });

            if (findAfterMax != arr.end()) {
                int value = *findAfterMax;
                size_t index = distance(arr.begin(), findAfterMax);
                arr.erase(findAfterMax);

                // Выводим массив после удаление
                cout << "arr after remove the next of max: ";
                copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
                cout << endl;

                cout << "Deleted value: Index = " << index << ", Value = " << value << endl;
            } else {
                cout << "No found number after the max element" << endl;
            }
        } else {
            cout << "Array is empty, has not elements" << endl;
            return;
        }

        // Подсчет положительных и отрицательных значений
        int countPositive = count_if(arr.begin(), arr.end(), [](int x) { return x > 0; });
        int countNegative = count_if(arr.begin(), arr.end(), [](int x) { return x < 0; });
        cout << "Positive: " << countPositive << ", Negative: " << countNegative << endl;
    }
};

/*
 *    g++ -o main main.cpp
 *    ./main text.txt
 *
Не удален следующий после макса
5 1 5
0 2 3 4 5

удален следующий после макса
5 1 5
0 3 4 5 2

Не удален следующий после макса, с отрицательными
5 -4 5
0 -2 3 5 4

 *
 * **/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "error input" << endl;
        return 1;
    }
    string filePath = argv[1];
    Srv srv(filePath);
    srv.inputInfo();
    srv.solve();
    return 0;
}

//
//1. [ ]: ничего не захватывает.
//2. [&]: захватывает все переменные по ссылке.
//3. [=]: захватывает все переменные по значению.
//4. [this]: захватывает указатель на текущий объект (т.е. позволяет обращаться к членам класса).