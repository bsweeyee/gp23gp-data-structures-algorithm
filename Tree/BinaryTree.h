#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <cstddef>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

enum EBTTraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER,
    BREATHFIRST
};

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

    void Print();
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

#endif

template<class T>
void Node<T>::Print() {
    printf("%i, ", Value);
}

template<class T>
int BinaryTree<T>::Height() {
    // implement height
    return 0;
}

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
}

template<class T>
void BinarySearchTree<T>:: Insert(T value) {
    Node<T>* n = BinaryTree<T>::Root;
    if (n == nullptr) {
        BinaryTree<T>::Root = new Node<T>(value, nullptr);
    } else {
        Insert(n, value);
    }    
}

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
void BinarySearchTree<T>:: Delete(T value) {
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
        if (output->Parent->Left != nullptr && output->Parent->Left->Value == value) output->Parent->Left = nullptr;
        else if (output->Parent->Right != nullptr && output->Parent->Right->Value == value) output->Parent->Right = nullptr; 

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

