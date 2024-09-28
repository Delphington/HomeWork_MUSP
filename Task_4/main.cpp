#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Solve final {
private:
    Solve() {};
public:
    static pair<int, int> countSymbol(string str, char one, char zero) {

        auto last = unique(str.begin(), str.end());
        str.erase(last, str.end());

        int first = count(str.begin(), str.end(), one);
        int second = count(str.begin(), str.end(), zero);

        return make_pair(first, second);;
    }
};


class SrvFile final {
private:
    static string info;
    SrvFile() {}
public:
    static bool inputInfo(string &path) {
        ifstream inputFile(path);

        if (!inputFile) {
            cerr << "Dont open. Dont read" << endl;
            return false;
        }
        stringstream buffer;
        buffer << inputFile.rdbuf(); // Читаем весь файл в строковый поток
        info = buffer.str();
        inputFile.close();
        return true;
    }

    static bool outputInfo(const string &path) {
        ofstream outputFile(path);

        if (!outputFile) {
            cerr << "Dont open. Dont write" << endl;
            return false;
        }
        outputFile << info; // Записываем данные в файл
        outputFile.close();
        return true; // Успешное завершение
    }

    static string getInfo() {
        return info;
    }

    static void setInfo(const string &info) {
        SrvFile::info = info;
    }
};
// Определение статической переменной
string SrvFile::info;


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Error, dont files name";
        throw std::runtime_error("Dont file's name");
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    SrvFile::inputInfo(input_file);

    //first -  единички  second - нолики
    pair<int, int> result = Solve::countSymbol(SrvFile::getInfo(), '1', '0');

    SrvFile::setInfo(std::to_string(result.first) + " " + std::to_string(result.second));

    SrvFile::outputInfo(output_file);


 /*   //TODO: INFO
        g++ -o main main.cpp
        ./main input.txt output.txt

        тест1:  1011 ->  2 1
        тест2: 000  -> 0 1
        **/

    return 0;
}