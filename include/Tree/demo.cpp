#include <iostream>
#include "BinarySearchTree.h"

int main() {
    int n = 10;
    srand(time(NULL));
    BinarySearchTree<int> * bst = new BinarySearchTree<int>();
    printf("--- original ---\n");
    for (int i=0; i<10; i++) {
        int v = std::rand() % 1000;                
        bst->Insert(v);
        printf("(%i: %i), ", i, v);
    }
    printf("\n");

    printf("height: %i\n", bst->Height());

    printf("--- preorder ---\n");    
    bst->Print(PREORDER);

    printf("--- inorder ---\n");    
    bst->Print(INORDER);

    printf("--- postorder ---\n");    
    bst->Print(POSTORDER);    
    
    printf("--- breadth first ---\n");
    bst->Print(BREATHFIRST);
    
    while(true) {
        int number;
        std::cout << "Enter number to delete: ";
        std::cin >> number;

        bst->Delete(number);
        printf("--- in order after deletion (%i) ---\n", number);  
        bst->Print(INORDER);

        if (bst->Size() == 0) break;        
    }

    delete bst;
}