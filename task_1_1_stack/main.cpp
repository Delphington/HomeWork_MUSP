#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

class SrvInfo {
private:
    static string info;

    SrvInfo() {}

public:

    static string openFile(const string &path) {
        ifstream inputFile(path);

        if (!inputFile) {
            cerr << "Dont open" << endl;
            return "";
        }
        stringstream buffer;
        buffer << inputFile.rdbuf(); // Читаем весь файл в строковый поток
        info = buffer.str();
        inputFile.close();
        return info;
    }

    static bool isNormalOrder() {
        stack<char> myStack;
        for (char c: info) {
            if (c == '(' || c == '{' || c == '[') {
                myStack.push(c);
            } else {
                if (myStack.empty() ||
                    (c == ')' && myStack.top() != '(') ||
                    (c == '}' && myStack.top() != '{') ||
                    (c == ']' && myStack.top() != '[')) {
                    return false;
                }
                myStack.pop();
            }
        }
        return myStack.empty();
    }
};


string SrvInfo::info = "";


int main() {

    const string PATH_TO_FILE = "D:\\_DELPGINGTON\\University\\Sem_3\\Musp\\task_1_1_stack\\info.txt";

    string str = SrvInfo::openFile(PATH_TO_FILE);

    if (str.empty()) {
        cout << "File is empty OR dont open";
    } else {
        if (SrvInfo::isNormalOrder()) {
            cout << "order is good \n";
            return 0;
        }
        cout << "order is not good";
    }
    return 0;
}