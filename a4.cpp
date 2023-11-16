#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;
struct Vec2 {
    float x,y;
    Vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

struct Vertex {
    Vec2* value;
    std::vector<Vertex*> neightbours;
    int id;

    Vertex() {
    }

    ~Vertex() {
        delete value;
    }
};

class Graph {
    public:
        std::vector<Vertex*> vertexList;
        
        Graph() {
        }

        ~Graph() {
            // delete vertexList; // does this also run the delete for all the Vertex class?
            // remove data from memory
            for(int i=0; i<vertexList.size(); i++) {
                delete vertexList[i];
            }
            vertexList.clear(); // does this deallocate vertexList from heap?            
        }

        void PrintVertices() {
           for(int i=0; i<vertexList.size(); i++) {
                printf("%i: (%f, %f)\n", i, vertexList[i]->value->x, vertexList[i]->value->y);        
           }
        }

        void PrintNeighbours() {
            for(int i=0; i<vertexList.size(); i++) {
                printf("--- ( %f, %f ) neighbours ---\n", vertexList[i]->value->x, vertexList[i]->value->y);
                for (int j=0; j<vertexList[i]->neightbours.size(); j++) {
                    printf("%i: (%f, %f)\n", j, vertexList[i]->neightbours[j]->value->x, vertexList[i]->neightbours[j]->value->y);        
                }                                
           }
        }                
        
        static std::vector<Vertex*> DFT(Vertex* startVertex, std::vector<Vertex*> discoveredList) {
            discoveredList.push_back(startVertex);
            std::vector<Vertex*> neighbours = startVertex->neightbours;
            for(int i=0; i<neighbours.size(); i++) {
                if (std::find(discoveredList.begin(), discoveredList.end(), neighbours[i]) == discoveredList.end()) {                    
                    discoveredList = DFT(neighbours[i], discoveredList);
                }
            }
            return discoveredList;
        };

        static std::vector<Vertex*> BFT(std::vector<Vertex*> visited, std::vector<Vertex*> unvisited) {
            int currentUnVisitedSize = unvisited.size();
            for (int i=0; i<currentUnVisitedSize; i++) {
                if (std::find(visited.begin(), visited.end(), unvisited[i]) == visited.end()) {
                    visited.push_back(unvisited[i]);
                }
                for (int j=0; j<unvisited[i]->neightbours.size(); j++) {
                    // if not yet visited and not already in unvisited list, add to unvisited list
                    if (std::find(visited.begin(), visited.end(), unvisited[i]->neightbours[j]) == visited.end() &&
                        std::find(unvisited.begin(), unvisited.end(), unvisited[i]->neightbours[j]) == unvisited.end()) {
                        unvisited.push_back(unvisited[i]->neightbours[j]);
                    }
                }
            }
            // if there are more unvisited then visited, then it means we need to continue traversing
            if (unvisited.size() > visited.size()) {
                visited = BFT(visited, unvisited);
            }
            return visited;
        };

        static std::vector<Vertex*> DFTEarlyExit(Vertex* startVertex, std::vector<Vertex*> discoveredList, int *count, int exitCount) {
            discoveredList.push_back(startVertex);
            *count = *count + 1;            
            std::vector<Vertex*> neighbours = startVertex->neightbours;
            for(int i=0; i<neighbours.size(); i++) {
                if (*count >= exitCount) {
                    return discoveredList;
                }
                if (std::find(discoveredList.begin(), discoveredList.end(), neighbours[i]) == discoveredList.end()) {                    
                    discoveredList = DFTEarlyExit(neighbours[i], discoveredList, count, exitCount);
                }                
            }            
            return discoveredList;
        };

        static std::vector<Vertex*> BFTEarlyExit(std::vector<Vertex*> visited, std::vector<Vertex*> unvisited, int *count, int exitCount) {
            int currentUnVisitedSize = unvisited.size();
            for (int i=0; i<currentUnVisitedSize; i++) {
                if (std::find(visited.begin(), visited.end(), unvisited[i]) == visited.end()) {
                    visited.push_back(unvisited[i]);
                    *count = *count + 1;
                    if (*count >= exitCount) {
                        return visited;
                    }
                }
                for (int j=0; j<unvisited[i]->neightbours.size(); j++) {
                    // if not yet visited and not already in unvisited list, add to unvisited list                    
                    if (std::find(visited.begin(), visited.end(), unvisited[i]->neightbours[j]) == visited.end() &&
                        std::find(unvisited.begin(), unvisited.end(), unvisited[i]->neightbours[j]) == unvisited.end()) {
                        unvisited.push_back(unvisited[i]->neightbours[j]);
                    }
                }
            }
            // if there are more unvisited then visited, then it means we need to continue traversing
            if (unvisited.size() > visited.size()) {
                visited = BFTEarlyExit(visited, unvisited, count, exitCount);
            }            
            return visited;
        };
        
        static std::vector<Vertex*> DFS(Vertex* startVertex, Vertex* targetVertex, std::vector<Vertex*> path) {            
            
            return path;
        };

        static std::vector<Vertex*> BFS(Vertex* startVertex, Vertex* targetVertex, std::vector<Vertex*> path) {
            return path;
        };
};

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

        void PrettyPrint() {
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
                printf(".");                
                x = v->value->x + 1;                            
            }
            printf("\n");
        }

        void PrettyPrint(std::vector<Vertex*> visited) {
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
                if (std::find(visited.begin(), visited.end(), v) == visited.end()) {
                    printf(".");                
                }
                else if (v == visited[visited.size() - 1])
                {
                    printf("C");
                }
                else {
                    printf("o");
                }                                
                x = v->value->x + 1;                            
            }
            printf("\n");        
        }      
};

int main() {
    Grid* grid = new Grid();
    std::string line;
    std::ifstream myfile ("GraphNodes.txt");
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

    // add neighbours here
    for(int i=0; i<n; i++) {        
        for (int j=0; j<n; j++) {
            if (j != i) {
                if (grid->vertexList[i]->value->x + 1 == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y == grid->vertexList[j]->value->y) {
                    grid->vertexList[i]->neightbours.push_back(grid->vertexList[j]);
                }
                if (grid->vertexList[i]->value->x - 1 == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y == grid->vertexList[j]->value->y) {
                    grid->vertexList[i]->neightbours.push_back(grid->vertexList[j]);
                }
                if (grid->vertexList[i]->value->x == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y + 1 == grid->vertexList[j]->value->y) {            
                    grid->vertexList[i]->neightbours.push_back(grid->vertexList[j]);
                }
                if (grid->vertexList[i]->value->x == grid->vertexList[j]->value->x && grid->vertexList[i]->value->y - 1 == grid->vertexList[j]->value->y) {            
                    grid->vertexList[i]->neightbours.push_back(grid->vertexList[j]);
                }                
            }
        }
    }    

    // grid->PrintVertices();
    // grid->PrintNeighbours();
    grid->PrettyPrint();
    
    printf("\n");
    printf("enter b for BFS\nenter d for DFS\n");
    char c = ' ';
    cin >> c;

    int count = 1;
    int currentCount = 0;                
        
    if (c == 'd') {
        // traverse in depth first order (from first vertex)
        // printf("--- depth first traversal ---\n");
        std::vector<Vertex*> dfoList;    
        while(count <= grid->vertexList.size()) {
            cin.ignore();
            dfoList.clear();
            dfoList = Graph::DFTEarlyExit(grid->vertexList[0], dfoList, &currentCount, count);
            grid->PrettyPrint(dfoList);
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
            cin.ignore();
            visited.clear();
            visited = Graph::BFTEarlyExit(visited, unvisited, &currentCount, count);
            grid->PrettyPrint(visited);
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