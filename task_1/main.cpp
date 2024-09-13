#include <iostream>
#include "ForwardList.h"
using namespace std;

int main() {
    ForwardList<int>  list;

    string is_empty = list.empty() ? "null" : "not null";
    cout << is_empty << endl;

    list.push_front(5);
    list.push_front(3);
    list.push_front(1);

    is_empty = list.empty() ? "null" : "not null";
    cout << is_empty << endl;


    std::cout << std::endl;
    std::cout << "list: ";
    while (!list.empty()) {
        std::cout << list.front() << " ";
        list.pop_front();
    }
    std::cout << std::endl;

    return 0;
}
