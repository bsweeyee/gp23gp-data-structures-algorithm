#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T> {
    private:
        void Insert(Node<T>* node, T value);
    public:
        BinarySearchTree() {
            BinaryTree<T>::Root = nullptr;
        }
        BinarySearchTree(Node<T>* root, Node<T>* left, Node<T>* right) {
            BinaryTree<T>::Root = root;
            BinaryTree<T>::Root->Parent = nullptr;
            BinaryTree<T>::Root->Left = left;
            BinaryTree<T>::Root->Right = right;

            BinaryTree<T>::Root->Left->Parent = root;
            BinaryTree<T>::Root->Right->Parent = root;
        }
        
        Node<T>* Find(T value);
        void Insert(T value);
        void Delete(T value);        
};

template<class T>
void BinarySearchTree<T>::Insert(Node<T>* node, T value) {
    if (value <= node->Value) {
        if (node->Left != nullptr) {
            Insert(node->Left, value);
        }
        else {
            node->Left = new Node<T>(value, node);            
        }        
    } else {
        if (node->Right != nullptr) {
            Insert(node->Right, value);
        }
        else {
            node->Right = new Node<T>(value, node);            
        }
    }
};

template<class T>
Node<T>* BinarySearchTree<T>::Find(T value) {
    std::stack<Node<T>*> s;
    s.push(BinaryTree<T>::Root);
    Node<T>* p = nullptr;
    Node<T>* output = nullptr;
    while(!s.empty()) {
        p = s.top();
        s.pop();

        if (p->Value == value) {
            output = p;
            break;
        }

        if (p->Right != nullptr) {
            s.push(p->Right);
        }
        if (p->Left != nullptr) {
            s.push(p->Left);
        }        
    }
    return output;   
}

template<class T>
void BinarySearchTree<T>::Insert(T value){
    Node<T>* n = BinaryTree<T>::Root;
    if (n == nullptr) {
        BinaryTree<T>::Root = new Node<T>(value, nullptr);
    } else {
        Insert(n, value);
    }  
};

template<class T>
void BinarySearchTree<T>::Delete(T value) {
    // find node to delete
    Node<T>* output = Find(value);
    if (output == nullptr) {
        printf("unable to find %i for deletion\n", value);
        return;
    }

    // account for when deletion is at Root
    if (output->Parent == nullptr) { // parent of root node is always null
        // take left tree as root and insert right tree
        if (output->Left != nullptr) {
            BinaryTree<T>::Root = output->Left;
            BinaryTree<T>::Root->Parent = nullptr;
            if (output->Right != nullptr) {
                int rightSize = BinaryTree<T>::Size(output->Right);
                T* rightValues = new T[rightSize];

                int rightCount = 0;
                rightValues = BinaryTree<T>::List(output->Right, rightValues, &rightCount, INORDER);
                for(int i=0; i<rightSize; i++) {
                    Insert(rightValues[i]);
                }     
                delete[] rightValues;
                delete output->Right; 
            }
        } 
        else if (output->Right != nullptr) { // otherwise only right tree exist, so set root to right 
            BinaryTree<T>::Root = output->Right;
            BinaryTree<T>::Root->Parent = nullptr;
        }
        else { // if left and right are null, this means we have deleted the whole tree so set root to null            
            BinaryTree<T>::Root = nullptr;
        }
    }
    else {
        // unlink parent node to this node
        if (output->Parent->Left != nullptr && output->Parent->Left == output) output->Parent->Left = nullptr;
        else if (output->Parent->Right != nullptr && output->Parent->Right == output) output->Parent->Right = nullptr; 

        // reinsert left tree
        if (output->Left != nullptr) {
            int leftSize = BinaryTree<T>::Size(output->Left);
            T* leftValues = new T[leftSize];
            
            int leftCount = 0;
            leftValues = BinaryTree<T>::List(output->Left, leftValues, &leftCount, INORDER);
            for(int i=0; i<leftSize; i++) {
                Insert(leftValues[i]);
            }

            delete[] leftValues;
            delete output->Left;
        }

        // reinsert right tree
        if (output->Right != nullptr) {
            int rightSize = BinaryTree<T>::Size(output->Right);
            T* rightValues = new T[rightSize];

            int rightCount = 0;
            rightValues = BinaryTree<T>::List(output->Right, rightValues, &rightCount, INORDER);
            for(int i=0; i<rightSize; i++) {
                Insert(rightValues[i]);
            }     
            delete[] rightValues;
            delete output->Right;            
        }
    }
    // we set output to null to ensure none of the nodes are referenced to when deleted ( even though they should already be deleted above )
    output->Left = nullptr;
    output->Right = nullptr;
    output->Parent = nullptr;
    delete output;  
}

#endif