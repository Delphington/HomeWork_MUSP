#pragma once

#include <memory>
#include <stdexcept>

using namespace std;

template<typename T>
class ForwardList {
private:
    struct Node {
        T data;
        shared_ptr<Node> next;

        Node(const T &data) : data(data), next(nullptr) {}
    };

    shared_ptr<Node> head;

public:
    ForwardList() : head(nullptr) {}

    void push_front(const T &data) {
        shared_ptr<Node> node = std::make_shared<Node>(data);
        node->next = head;
        head = node;
    }

    void pop_front() {
        if (head != nullptr) {
            head = head->next;
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    T &front() const {
        if (!empty())
            return head->data;
    }
};