#ifndef _BINARY_TREE_NODE_H_
#define _BINARY_TREE_NODE_H_

template<class T>
struct Node {
    Node() {
        Left = nullptr;
        Right = nullptr;
    }
    Node(T value, Node<T>* parent) {
        Value = value;
        Left = nullptr;
        Right = nullptr;

        Parent = parent;
    }
    ~Node() {
        // delete Value;
        delete Left;
        delete Right;

        Left = nullptr;
        Right = nullptr; 
        Parent = nullptr;       
    }        
    T Value;
    Node<T>* Parent;
    Node<T>* Left;
    Node<T>* Right; 

    void Print() {
        printf("%i, ", Value);
    };
};

#endif