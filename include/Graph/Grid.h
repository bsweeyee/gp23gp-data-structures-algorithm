#ifndef _GRID_H_
#define _GRID_H_

#include "Graph.h"

class Grid : public Graph {
    public:    
        Vec2* size;

        Grid() {
            size = new Vec2(0, 0);             
        }

        ~Grid() {
            // delete vertexList; // does this also run the delete for all the Vertex class?
            // remove data from memory
            for(int i=0; i<vertexList.size(); i++) {
                delete vertexList[i];
            }
            vertexList.clear(); // does this deallocate vertexList from heap?            
        }

        void PrettyPrint();           
        void PrettyPrint(std::vector<Vertex*> visited, Vertex* target);                 
};

#endif

void Grid::PrettyPrint() {
    float y = 0;
    float x = 0;
    for(Vertex* v: vertexList) {
        if (v->value->y > y) {
            while(x < size->x) {
                printf("X");
                x += 1;                        
            }
            printf("\n");
            x = 0;
            y = v->value->y;
        }
        while(v->value->x > x) {
            printf("X");
            x += 1;
        }                                
        printf("*");                
        x = v->value->x + 1;                            
    }
    printf("\n");
}

void Grid::PrettyPrint(std::vector<Vertex*> visited, Vertex* target) {
    float y = 0;
    float x = 0;
    for(Vertex* v: vertexList) {
        if (v->value->y > y) {
            while(x < size->x) {
                printf("X");
                x += 1;                        
            }
            printf("\n");                    
            x = 0;
            y = v->value->y;
        }
        while(v->value->x > x) {
            printf("X");
            x += 1;
        }
        if (v == visited[visited.size() - 1])
        {                    
            printf("C");                    
        }                
        else if (std::find(visited.begin(), visited.end(), v) == visited.end()) {
            if (target != nullptr && v == target) {
                printf("H");
            } else {
                printf("*");                
            }
        }                                                
        else {
            printf("o");
        }                                                
        x = v->value->x + 1;                            
    }
    printf("\n");        
}     