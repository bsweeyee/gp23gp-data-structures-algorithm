#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include <iostream>

template<class T>
struct Node {
    T Value;
    Node<T>* Next; 
};

template<class T>
class LinkedList {
    public:
        LinkedList() {
            Length = 0;
        }

        ~LinkedList() {
            Dispose();
        }

        Node<T>* Head;
        Node<T>* Last;
        int Length;
        
        void Insert(int idx, T value);
        void Append(T value);
        void Delete(int idx);
        Node<T>* Find(T value);        
        Node<T>* FindAt(int idx);

        void Print();
        void Dispose();
};
#endif

template<class T>
void LinkedList<T>::Insert(int idx, T value) {
    if (idx >= Length) { 
        printf("index is larger then size of LinkedList\n");
        return;
    }
    Node<T>* newNode = new Node<T>();
    Node<T>* insertNode = FindAt(idx);    
    
    newNode->Value = value;
    if (idx == 0) {
        newNode->Next = insertNode;
        Head = newNode;
    } else {
        newNode->Next = insertNode->Next;
        insertNode->Next = newNode;
    }

    if (idx == Length - 1) {
        Last = newNode;
    }
    
    Length += 1;
}

template<class T>
void LinkedList<T>::Append(T value) {    
    Node<T>* newNode = new Node<T>();
    newNode->Value = value;
    if (Length == 0) {
        Head = newNode;        
    } else {
        Node<T>* n = FindAt(Length - 1);
        n->Next = newNode;
    }
    Length += 1;
    Last = newNode;
}

template<class T>
void LinkedList<T>::Delete(int idx) {
    if (idx >= Length) {
        printf("index is larger then size of LinkedList\n");
        return;
    }

    Node<T>* n = FindAt(idx);
    if (idx == 0) {
        Head = n->Next;
    } else {
        Node<T>* d = FindAt(idx - 1);
        d->Next = n->Next;
        if (idx == Length - 1) {
            Last = d;
        }
    }
    delete n;

    Length -= 1;
}

template<class T>
Node<T>* LinkedList<T>::Find(T value) {
    Node<T>* n = Head;
    while(n != nullptr) {
        if (n->Value == value) {
            return n;
        }
        n = n->Next;
    }
    return nullptr;
} 

template<class T>
Node<T>* LinkedList<T>::FindAt(int idx) {    
    if (idx == 0) { 
        if (Head == nullptr) Head = new Node<T>();
        return Head;
    }

    Node<T>* n = Head;
    int i = 0;
    while(i < idx) {                
        n= n->Next;
        i++;
    }    
    return n;
}

template<class T>
void LinkedList<T>::Print() {
    Node<T>* n = Head;
    while(n != nullptr) {
        printf("%i, ", n->Value);
        n = n->Next;
    }
    printf("\n");
}

template<class T>
void LinkedList<T>::Dispose() {
    Node<T>* n = Head;
    while(n != nullptr) {
        Node<T>* d = n;
        n = n->Next;
        delete d;        
    }
}