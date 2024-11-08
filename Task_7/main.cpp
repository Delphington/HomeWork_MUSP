#include <iostream>
#include <fstream>
#include <windows.h>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

class Statictic {
private:
    string nameCategory;
    pair<string, int> minPriceGod;
    pair<string, int> maxPriceGod;
    int amountGods;
    double income;


    void updateMinPriceGod(string &nameGod, double price) {
        if (minPriceGod.second > price) {
            minPriceGod.first = nameGod;
            minPriceGod.second = price;
        }
    }

    void updateMaxPriceGod(string &nameGod, double price) {
        if (maxPriceGod.second < price) {
            maxPriceGod.first = nameGod;
            maxPriceGod.second = price;
        }
    }

    void sumIncome(double item, int am) {
        income += item * am;
    }


public:
    Statictic(string &nameGod, string &nameCategory, double price) : amountGods(0), income(0.0f) {
        this->nameCategory = nameCategory;
        minPriceGod = make_pair(nameGod, price);
        maxPriceGod = make_pair(nameGod, price);
    }

    void calculate(string &nameGod, int am, double price) {
        amountGods += am;
        updateMinPriceGod(nameGod, price);
        updateMaxPriceGod(nameGod, price);
        sumIncome(price, am);
    }

    int getAmountGods() const {
        return amountGods;
    }

    double getIncome() const {
        return income;
    }

    pair<string, int> getMinPriceGod() const {
        return minPriceGod;
    }

    pair<string, int> getMaxPriceGod() const {
        return maxPriceGod;
    }
};

//------------------------

class Srv {
private:
    string path;
    map<string, Statictic> mapa;

    vector<string> splitString(const string &str) {
        vector<string> words;
        stringstream ss(str);
        string word;

        while (getline(ss, word, ',')) {
            words.push_back(word);
        }

        return words;
    }

public:
    Srv(const string &path) {
        this->path = path;
    }

    void inputInfo() {
        ifstream inputFile(path);

        if (!inputFile) {
            cerr << "Dont open" << endl;
            return;
        }

        string line;
        while (std::getline(inputFile, line)) {
            updateMapa(line);
        }
        inputFile.close();
    }


    void updateMapa(string &line) {
        vector<string> wods = splitString(line);
//        for (int i = 0; i < wods.size(); i++) {
//            cout << wods[i] << ":";
//        }
//        cout << endl;

        //Dell Inspiron 15:ноутбук:4:849.99:
        string type = wods[1];
        string name = wods[0];
        int amount;
        double price;
        try {
            amount = (stod(wods[2]));
            price = stod(wods[3]);
        } catch (...) {
            cout << "ERROR преобразования" << endl;
            return;
        }

        if (mapa.count(type) == 0) {
            Statictic st = Statictic(name, type, price);
            st.calculate(name, amount, price);
            mapa.insert({type, st});

        } else {
            auto it = mapa.find(type);
            if (it != mapa.end()) {
                it->second.calculate(name, amount, price);
            } else {
                // Обработка случая, если ключ все еще не найден
                std::cerr << "Ошибка: ключ '" << type << "' не найден в карте." << std::endl;
            }

        }
//        cout << endl;
    }

    void printStatictic(const Statictic &obj) {
        cout << "Общее число товаров: " << obj.getAmountGods() << endl;
        cout << "Доход: " << obj.getIncome() << endl;
        cout << "Товар с минимальной ценой: " << obj.getMinPriceGod().first << ", цена: " << obj.getMinPriceGod().second
             << endl;
        cout << "Товар с максимальной ценой: " << obj.getMaxPriceGod().first << ", цена: "
             << obj.getMaxPriceGod().second << endl;
    }

    void printMapa() {
        for (map<string, Statictic>::const_iterator it = mapa.begin(); it != mapa.end(); ++it) {
            cout << "===================================" << endl;
            cout << "======= Категория: " << it->first << " =======" << endl;
            printStatictic(it->second);
            cout<<endl;
        }
    }

};

/*
 *    g++ -o main main.cpp
 *    ./main goods.txt
 **/
int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc != 2) {
        cout << "error input" << endl;
        return 1;
    }
    string filePath = argv[1];
    Srv srv(filePath);
    srv.inputInfo();
    srv.printMapa();
    return 0;
}
