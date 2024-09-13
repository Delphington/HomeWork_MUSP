#pragma once

#include <memory>
#include <stdexcept>
using  namespace std;

template<class T>
class ForwardListFalse {
private:
    struct Node {
        T date;
        unique_ptr<Node> next;

        Node(const T &date);
    };

    unique_ptr<Node> curr;

public:
    ForwardListFalse();
    void pushFront(const T &t);
    void popFront();
    bool empty() const;
    const T &front() const;
};

