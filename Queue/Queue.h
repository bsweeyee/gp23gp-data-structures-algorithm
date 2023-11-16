#ifndef _QUEUE_H
#define _QUEUE_H
#include "../LinkedList/LinkedList.h"

template<class T>
class Queue : LinkedList<T> {
    public:
        void Enqueue(T value);
        T Dequeue();
        T Peek();
};

#endif

template<class T>
void Queue<T>::Enqueue(T value) {
    Append(value);
}

template<class T>
T Queue<T>::Dequeue() {
    Node<T>* n = FindAt(0);
    T v = n->Value;
    Delete(0);
    return v;
}

template<class T>
T Queue<T>::Peek() {
    Node<T>* n = FindAt(0);
    return n->Value;
}