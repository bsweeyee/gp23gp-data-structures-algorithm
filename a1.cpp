#include <iostream>
#include <vector>
#include <string>
#include "LinkedList/LinkedList.h"

using namespace std;

struct Tree {
    float y;
    float z;
    float x;
};


int main()
{
    // allocate array on heap but struct on stack(?) method
    Tree* treeArray = new Tree[100];
    {        
        for (int i=0; i<100; i++) {
            Tree t; // QUESTION: where is this Tree struct memory allocated when i assign it to treeArray?
            t.x = std::rand() % 100;
            t.y = std::rand() % 100;
            t.z = std::rand() % 100;

            treeArray[i] = t; // the moment it gets assigned here, it goes to the heap
            // cout << i << ": (" << treeArray[i].x << ", " << treeArray[i].y << ", " << treeArray[i].z << ")";
            // cout << endl;
        }
    }

    // for(int i=0; i<100; i++) {
    //     delete treeArray[i]; // if Tree is allocated on the heap, then this scalar delete should work but it does not
    // }

      
    delete[] treeArray; /// this deallocates memory of the entire array and the values inside

    // QUESTION: is this safer then having each of the Tree entry be dynamically allocated? 


    // cout << "after delete 0: (" << treeArray[0].x << ", " << treeArray[0].y << ", " << treeArray[0].z << ")";
    // cout << endl;

    // allocate tree array on stack, but Tree struct on heap method
    Tree* treeArray2[100]; 
    {
        for (int i=0; i<100; i++) {
            Tree* t = new Tree();
            t->x = std::rand() % 100;
            t->y = std::rand() % 100;
            t->z = std::rand() % 100;
            treeArray2[i] = t;

            // cout << i << ": (" << treeArray[i]->x << ", " << treeArray[i]->y << ", " << treeArray[i]->z << ")";
            // cout << endl;
        }    
    }

    for(int i=0; i<100; i++) {
        delete treeArray2[i];
    }

    Tree** treeArray3 = new Tree*[100]; // if we want both the array and the Tree struct to be manually heap allocated, we need to do this double pointer method
    
    cout << "0: (" << treeArray[0].x << ", " << treeArray[0].y << ", " << treeArray[0].z << ")";
    cout << endl;
}