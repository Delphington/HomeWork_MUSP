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


    int static isNormalOrder() {
        stack<int> stack;
        for (int index = 0; index < info.length(); index++) {
            char ch = info[index];

            if (ch == '(' || ch == '[' || ch == '{') {
                stack.push(index);
            } else if (ch == ')' || ch == ']' || ch == '}') {

                if (stack.empty()) {
                    //нет пары для закрытой
                    return index;
                }

                //если ошибка с парами закрывающая не соответсвует
                char top = info[stack.top()];
                if ((ch == ')' && top != '(') ||
                    (ch == ']' && top != '[') ||
                    (ch == '}' && top != '{')) {
                    return index;
                }
                stack.pop();
            }
        }

        //остались откртые скобки не закрыты
        if (!stack.empty()) {
            return stack.top();
        }

        return -1; // Ввсе гуд
    }

};


string SrvInfo::info = "";


int main() {

//    const string PATH_TO_FILE = "D:\\_DELPGINGTON\\University\\Sem_3\\Musp\\task_1_1_stack\\info.txt";
//
//    string str = SrvInfo::openFile(PATH_TO_FILE);
//
//    if (str.empty()) {
//        cout << "File is empty OR dont open";
//    } else {
//        int ans = SrvInfo::isNormalOrder();
//        if (ans == -1) {
//            cout << "success";
//        } else {
//            cout << ans;
//        }
//    }


        int s,t;
        cin>>s;
        cin>> t;
        if(s>5 &&   t>5){
            cout<<"Yes";
        }else{
            cout<<"No";
        }

    return 0;
}