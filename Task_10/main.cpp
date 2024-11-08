#include <iostream>
#include <regex>
#include <filesystem>
#include <windows.h>

using namespace std;
namespace fs = filesystem;

class Srv{
public:
    static pair<string, string> getParametr(int argc, char *argv[]){
        string findStr;
        string replaceStr;
        if (argc == 4) {
            findStr = argv[2];
            replaceStr = argv[3];
        } else {
            findStr = argv[3];
            replaceStr = argv[4];
        }
        return make_pair(findStr,replaceStr);
    }

    static bool isRegularExp(int argc, char *argv[]){
        return (argc == 5 && strcmp(argv[2], "-r") == 0);
    }


    static string strReplace(string str, string findStr, string replaceStr) {
        size_t index = 0;
        while (true) {
            index = str.find(findStr, index);
            if (index == string::npos) { //find string - не найден
                break;
            }
            str.replace(index, findStr.size(), replaceStr);
            index += findStr.size();
        }
        return str;
    }
};

//Todo:
/**
  g++ -o main main.cpp
 ./main Dir try hello
 ./main Dir -r hel* Capybara
 ./main Dir/Some Capybara telk
*/

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 4 && argc != 5) {
        cout << "Error input" << endl;
        return 1;
    }

    //  / - объединение
    fs::path dir = fs::current_path() / argv[1];
    if (!fs::exists(dir)) {
        throw runtime_error("Директория не существует");
    }
    if (!fs::is_directory(dir)) {
        throw runtime_error(dir.string() + " Это не является директорией");
    }
    //-------------------------------------------
    bool useRegex = Srv::isRegularExp(argc, argv);

    pair<string, string> parametr = Srv::getParametr(argc, argv);


    for (auto &entry: fs::recursive_directory_iterator(dir)) {
        string filename;
        if (useRegex) {
            filename = regex_replace(entry.path().filename().string(), regex(parametr.first), parametr.second);

            fs::rename(entry, entry.path().parent_path() / filename);
        } else {
            filename = Srv::strReplace(entry.path().filename().string(), parametr.first, parametr.second);
            fs::rename(entry, entry.path().parent_path() / filename);
        }
    }
    return 0;
}