#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;



class SrvFile final {
private:
    string first;
    string info;

    int N;
    vector<int> arr;

    int res;

public:
    SrvFile() = default;

     void inputInfo(string &path) {
        ifstream inputFile(path);

        if (!inputFile) {
            cerr << "Dont open. Dont read" << endl;
            return;
        }

        int cnt = 0;
        std::string line;
        while (std::getline(inputFile, line)) {
            if (cnt ==0){
                first = line;
                cnt++;
            }else{
                info = line;
            }
        }
        inputFile.close();
    }


    void dataNormalization(){
        try{
            N = std::atoi(first.c_str()); // Преобразуем строку в int
            // сплитим
            size_t pos = 0;
            while ((pos = info.find(' ')) != std::string::npos) {
                arr.push_back(std::stoi(info.substr(0, pos)));
                info.erase(0, pos + 1);
            }
            // Добавляем последнее число
            if (!info.empty()) {
                arr.push_back(std::stoi(info));
            }
        }catch (...){
            cerr<<"Error to int";
        }
    }


    void solve(){
        sort(arr.begin(), arr.end());

        int sum1 = std::accumulate(arr.begin(), arr.end() - N/2, 0); // Суммирует элементы
        int sum2 = std::accumulate(arr.end() -N/2, arr.end(), 0); // Суммирует элементы
        res =  sum2 -sum1;
    }


    void outputInfo(const string &path) {
        ofstream outputFile(path);

        if (!outputFile) {
            cerr << "Dont open. Dont write" << endl;
            return;
        }
        outputFile << res; // Записываем данные в файл
        outputFile.close();
    }
};


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Error, dont files name";
        throw std::runtime_error("Dont file's name");
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    SrvFile srvFile;

    srvFile.inputInfo(input_file);

    srvFile.dataNormalization();

    srvFile.solve();

    srvFile.outputInfo(output_file);


    /*   //TODO: INFO
           g++ -o main main.cpp
           ./main input.txt output.txt

           тест1:
           2
           1 3 -> 2
           тест2:
           4
           3 1 8 100  -> 104
           **/

    return 0;
}