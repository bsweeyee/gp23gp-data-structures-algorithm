#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <cstddef>
#include <iostream>
#include <stack>
#include <queue>
#include "Node.h"

enum EBTTraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER,
    BREATHFIRST
};

template<class T>
class BinaryTree {
    protected:
        Node<T>* Root;
    public:
        BinaryTree() {
            Root = nullptr;
        }
        BinaryTree(Node<T>* root, Node<T>* left, Node<T>* right) {
            Root = root;
            Root->Parent = nullptr;
            Root->Left = left;
            Root->Right = right;

            Root->Left->Parent = root;
            Root->Right->Parent = root;
        }
        ~BinaryTree() {
            delete Root;            
        }

        int Height();
        int Size();
        T* List(T* list, int* count, EBTTraverseOrder order);
        void Print(EBTTraverseOrder order);
        
        // TODO: SubTrees assigns memory to heap. need to find a way to delete tree without also deleting nodes to prevent memory leak
        static BinaryTree<T>* SubTree(Node<T>* root) {
            return new BinaryTree<T>(root, root->Left, root->Right);
        };
        
        static T* List(Node<T>* node, T* list, int* count, EBTTraverseOrder order) {
            switch(order) {
                case INORDER:
                if (node->Left != nullptr) list = BinaryTree<T>::List(node->Left, list, count, order);        
                
                list[*count] = node->Value;
                *count = *count + 1;
                
                if(node->Right != nullptr) list = BinaryTree<T>::List(node->Right, list, count, order);                       
                break;
                case PREORDER:
                list[*count] = node->Value;
                *count = *count + 1;
                
                if (node->Left != nullptr) list = BinaryTree<T>::List(node->Left, list, count, order);
                if (node->Right != nullptr) list = BinaryTree<T>::List(node->Right, list, count, order);
                break;
                case POSTORDER:
                if (node->Right != nullptr) list = BinaryTree<T>::List(node->Right, list, count, order);

                list[*count] = node->Value;
                *count = *count + 1;

                if (node->Left != nullptr) list = BinaryTree<T>::List(node->Left, list, count, order);
                break;
                case BREATHFIRST:
                std::queue<Node<T>*> q;
                q.push(node);
                Node<T>* p = nullptr;                

                while(!q.empty()) {
                    p = q.front();
                    q.pop();
                    // printf("%i\n", p->Value);
                    
                    list[*count] = p->Value;
                    *count = *count + 1;

                    if (p->Left != nullptr) {
                        q.push(p->Left);
                    }
                    if (p->Right != nullptr) {
                        q.push(p->Right);
                    }
                }
                break;
            }
            return list;
        };
        
        static int Size(Node<T>* root) {
            int size = 0;    
            if (root == nullptr) return size;

            std::stack<Node<T>*> s;
            s.push(root);
            Node<T>* p = nullptr;
            while(!s.empty()) {
                p = s.top();
                s.pop();                

                if (p->Right != nullptr) {
                    s.push(p->Right);
                }
                if (p->Left != nullptr) {
                    s.push(p->Left);
                }
                size = size + 1;
            }     

            return size;
        }        
};

template<class T>
void BinaryTree<T>::Print(EBTTraverseOrder order) {
    if (Root == nullptr) { 
        printf("{}");
        return;
    }

    int size = Size();
    T* list = new T[size];
    int count = 0;
    list = List(Root, list, &count, order);
    for(int i=0; i<size; i++) {
        printf("%i, ", list[i]);
    }
    printf("\n");
    delete[] list;
}

template<class T>
T* BinaryTree<T>::List(T* list, int* count, EBTTraverseOrder order) {
    return BinaryTree<T>::List(Root, list, count, order);
}

template<class T>
int BinaryTree<T>::Size() {
    return BinaryTree<T>::Size(Root);
}

template<class T>
int BinaryTree<T>::Height() {
    if (Root == nullptr) return 0;
    
    std::queue<Node<T>*> q;
    q.push(Root);
    Node<T>* p = nullptr;                
    int height = 0;    
    int largest = 0;

    while(!q.empty()) {
        p = q.front();
        q.pop();

        if (p->Value < largest) {
            height = height + 1;
        }
        largest = p->Value;

        if (p->Left != nullptr) {
            q.push(p->Left);
        }
        if (p->Right != nullptr) {
            q.push(p->Right);
        }
    }
    return height;
}

#endif