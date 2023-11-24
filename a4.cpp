#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include "Graph/Grid.h"

int main() {
    srand(time(NULL));
    Grid* grid = new Grid();
    std::string line;
    std::ifstream myfile ("data/GraphNodes.txt");
    // open file here
    int x = 0, y = 0, idx = 0;    
    if (myfile.is_open()) {
        while ( getline (myfile, line) ) {
            // loop each line, parse o or x. if o, add position, else skip. top left is (0, 0)            
            for(char& c: line) {
                Vertex* v = new Vertex();
                if (c == 'o') {
                    v->value = new Vec2(x, y);
                    v->id = idx;
                    grid->vertexList.push_back(v);
                    idx += 1;                    
                }
                x += 1;
            }
            grid->size->x = x;
            x = 0;
            y += 1;
        }
        grid->size->y = y;
        myfile.close();
    }
    else { 
        printf("Unable to open file\n");
        return 0;
    }
    int n = grid->vertexList.size();

    // int n = 10;    
    // int idx = 0;
    // for(int i=0; i<n/2; i++) {
    //     for (int j = 0; j<n/2; j++) {
    //         Vertex* v = new Vertex();
    //         // printf("(%i, %i)", i, j);            
    //         v->value = new Vec2(i, j);
    //         v->id = idx;
    //         grid->vertexList.push_back(v);
    //         idx += 1;
    //     }
    // }    

    // add neighbours here, TODO: refactor this into Graph
    for(int i=0; i<n; i++) {        
        for (int j=0; j<n; j++) {
            if (j != i) {
                // float weight = std::rand() % 100;
                float weight = 1;
                bool isAdd = false;

                if (grid->vertexList[i]->value->x + 1 == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y == grid->vertexList[j]->value->y) {
                    // we should be able to just check for 1 side because we will be adding neighbours to both sides
                    isAdd = true;           
                }
                if (grid->vertexList[i]->value->x - 1 == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y == grid->vertexList[j]->value->y) {
                    isAdd = true;
                }
                if (grid->vertexList[i]->value->x == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y + 1 == grid->vertexList[j]->value->y) {            
                    isAdd = true;
                }
                if (grid->vertexList[i]->value->x == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y - 1 == grid->vertexList[j]->value->y) {            
                    isAdd = true;
                }

                if (isAdd) {
                    auto found1 = std::find(grid->vertexList[i]->neightbours.begin(), grid->vertexList[i]->neightbours.end(), grid->vertexList[j]);
                    // auto found2 = std::find(grid->vertexList[j]->neightbours.begin(), grid->vertexList[j]->neightbours.end(), grid->vertexList[i]);
                    
                    if (found1 == grid->vertexList[i]->neightbours.end()) {
                        grid->vertexList[i]->neightbours.push_back(grid->vertexList[j]);
                        grid->vertexList[i]->neighbourEdgeWeights[grid->vertexList[j]] = weight;                    
                        grid->vertexList[j]->neightbours.push_back(grid->vertexList[i]);                                
                        grid->vertexList[j]->neighbourEdgeWeights[grid->vertexList[i]] = weight;
                    }
                }                
            }
        }
    }
    // randomly pick a start and end vertex
    int startVertexIdx = rand() % grid->vertexList.size();
    int endVertexIdx = rand() % grid->vertexList.size();    

    // grid->PrintVertices();
    // grid->PrintNeighbours();
    grid->PrettyPrint();
    
    printf("\n");
    printf("enter b for BFS\nenter d for DFS\nenter a for AStar\n");
    char c = ' ';
    std::cin >> c;

    int count = 1;
    int currentCount = 0;                
    if (c == 'a') {
        std::vector<Vertex*> path = grid->Astar(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx]);
        // printf("---- start: (%f, %f), end: (%f, %f) ----\n", grid->vertexList[startVertexIdx]->value->x, grid->vertexList[startVertexIdx]->value->y, grid->vertexList[endVertexIdx]->value->x, grid->vertexList[endVertexIdx]->value->y);
        // for(Vertex* v:path) {
        //     printf("(%f, %f), ", v->value->x, v->value->y);
        // }
        // printf("\n");
        std::vector<Vertex*> temp;
        int idx = 0;
        do {
            std::cin.ignore();            
            temp.push_back(path[idx]);
            grid->PrettyPrint(temp, path[path.size()-1]);
            idx += 1;                        
        } while(temp.size() < path.size());

    } else if (c == 'd') {
        // traverse in depth first order (from first vertex)
        // printf("--- depth first traversal ---\n");
        std::vector<Vertex*> dfoList;    
        while(count <= grid->vertexList.size()) {
            std::cin.ignore();
            dfoList.clear();
            dfoList = Graph::DFTEarlyExit(grid->vertexList[0], dfoList, &currentCount, count);
            grid->PrettyPrint(dfoList, nullptr);
            count += 1;
            currentCount = 0;        
        }
        // dfoList = Graph::DFT(grid->vertexList[0], dfoList);
        // for(int i=0; i<dfoList.size(); i++) {
        //     printf("%i: (%f, %f), ", i, dfoList[i]->value->x, dfoList[i]->value->y);
        // }
    } else if (c == 'b') {
        std::vector<Vertex*> visited;
        std::vector<Vertex*> unvisited;
        unvisited.push_back(grid->vertexList[0]);
        while(count <= grid->vertexList.size()) {
            std::cin.ignore();
            visited.clear();
            visited = Graph::BFTEarlyExit(visited, unvisited, &currentCount, count);
            grid->PrettyPrint(visited, nullptr);
            count += 1;
            currentCount = 0;        
        }
        // visited = Graph::BFT(visited, unvisited);
        // for(int i=0; i<visited.size(); i++) {
        //     printf("%i: (%f, %f), ", i, visited[i]->value->x, visited[i]->value->y);
        // }
        // printf("\n");
    } else {
        printf("not a valid traversal option");
    }
    delete grid;
}