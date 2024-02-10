#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    LinkedList<int>* ll = new LinkedList<int>();
    
    // test append
    printf("--- Test Append ----\n");
    for(int i=0; i<100; i++) {
        ll->Append(i);
    }
    ll->Print();
    printf("last value: %i\n", ll->Last->Value);
    
    // // test delete
    printf("--- Test Delete ----\n");
    ll->Delete(99);
    ll->Print();
    printf("last value: %i\n", ll->Last->Value);

    // // test find
    printf("--- Test Find ----\n");
    int search = 75;
    Node<int>* n = ll->Find(search);
    if (n != nullptr) {
        printf("found in LinkedList: %i\n", n->Value);
    } else {
        printf("not found in LinkedList: %i\n", search);
    }

    // // test insert
    printf("--- Test Insert ----\n");
    ll->Insert(99, -1);
    ll->Print();

    ll->Insert(45, -1);
    ll->Print();

    delete ll;
}