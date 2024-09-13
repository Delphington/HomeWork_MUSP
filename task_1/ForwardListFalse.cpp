#include "ForwardListFalse.h"

// Реализация конструктора Node
template<class T>
ForwardListFalse<T>::Node::Node(const T &date) : date(date), next(nullptr) {}

// Реализация конструктора ForwardListFalse
template<class T>
ForwardListFalse<T>::ForwardListFalse() : curr(nullptr) {}

// Реализация метода pushFront
template<class T>
void ForwardListFalse<T>::pushFront(const T &t) {
    auto node = std::make_unique<Node>(t); // Используем make_unique для создания узла
    node->next = std::move(curr); // Перемещаем указатель на текущий объект
    curr = std::move(node); // Обновляем текущий указатель
}

// Реализация метода popFront
template<class T>
void ForwardListFalse<T>::popFront() {
    if (!empty()) {
        curr = std::move(curr->next);
    } else {
        throw std::runtime_error("ForwardListFalse is empty");
    }
}

// Реализация метода empty
template<class T>
bool ForwardListFalse<T>::empty() const {
    return curr == nullptr;
}

// Реализация метода front
template<class T>
const T &ForwardListFalse<T>::front() const {
    if (empty()) {
        throw std::runtime_error("ForwardListFalse is empty");
    }
    return curr->date;
}
