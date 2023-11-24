#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include "Vertex.h"

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

        std::vector<Vertex*> Astar(Vertex* startVertex, Vertex* targetVertex);        
        float Heuristic(Vertex* from, Vertex* goal);    
        float d(Vertex* v1, Vertex* v2);
        
        void PrintVertices();
        void PrintNeighbours();            
    private:    
        int Abs(int x);         
        std::vector<Vertex*> reconstructPath(std::map<Vertex*, Vertex*> cameFrom, Vertex* current);            

};

#endif

void Graph::PrintVertices() {
    for(int i=0; i<vertexList.size(); i++) {
        printf("%i: (%f, %f)\n", i, vertexList[i]->value->x, vertexList[i]->value->y);        
    }
}

void Graph::PrintNeighbours() {
    for(int i=0; i<vertexList.size(); i++) {
        printf("--- ( %f, %f ) neighbours ---\n", vertexList[i]->value->x, vertexList[i]->value->y);
        for (int j=0; j<vertexList[i]->neightbours.size(); j++) {
            printf("%i: (%f, %f), %f\n", j, vertexList[i]->neightbours[j]->value->x, vertexList[i]->neightbours[j]->value->y, vertexList[i]->neighbourEdgeWeights[vertexList[i]->neightbours[j]]);        
        }                                
    }
}

std::vector<Vertex*> Graph::Astar(Vertex* startVertex, Vertex* targetVertex) {
    std::vector<Vertex*> openSet;
    std::map<Vertex*, Vertex*> cameFrom;
    std::map<Vertex*, float> gScore;
    std::map<Vertex*, float> fScore;

    // we initialize the maps
    for(Vertex* v: vertexList) {
        cameFrom[v] = nullptr;
        gScore[v] = std::numeric_limits<float>::infinity();
        fScore[v] = std::numeric_limits<float>::infinity();
    }

    // start checking path from start vertex
    gScore[startVertex] = 0;
    fScore[startVertex] = Heuristic(startVertex, targetVertex);
    openSet.push_back(startVertex);
    
    while(openSet.size() > 0) {
        // find vertex in open set with lowest f score
        
        float lowestFScore = std::numeric_limits<float>::infinity();
        Vertex* current = nullptr;
        for (Vertex* v : openSet) {
            if (fScore[v] < lowestFScore) {
                current = v;
                lowestFScore = fScore[v];
            }
        }

        // we exit because we found the path to target vertex
        if (current == targetVertex) {
            return reconstructPath(cameFrom, current);
        }

        // remove element from open set
        for(int i=0; i<openSet.size(); i++) {
            if (openSet[i] == current) {
                openSet.erase(openSet.begin() + i);
                break;
            }
        }

        for(Vertex* neighbour: current->neightbours) {
            float tentative_gScore = gScore[current] + d(current, neighbour);
            // float tentative_fScore = gScore[current] + d(current, neighbour) + Heuristic(current, neighbour); 
            // QN: why do we update cameFrom neighbour when only gScore is lower?
            // ANS: It depends on use case. If we only use fScore we might miss some nodes 
            if (tentative_gScore < gScore[neighbour]) {
            // if (tentative_fScore < fScore[neighbour]) {
                cameFrom[neighbour] = current;
                gScore[neighbour] = tentative_gScore;
                fScore[neighbour] = tentative_gScore + Heuristic(current, neighbour);
                // fScore[neighbour] = tentative_fScore;

                // check if neighour is in open set, add it in if it is. TODO: check for cleaner find function
                bool isNeighbourInOpenSet = false;
                for(Vertex* v : openSet) {
                    if (v == neighbour) {
                        isNeighbourInOpenSet = true;                                
                    }
                }
                if (!isNeighbourInOpenSet) {
                    openSet.push_back(neighbour);
                }
            }
        }
    }
    return openSet; // at this point, open set should be empty, so failure
}

float Graph::Heuristic(Vertex* from, Vertex* goal) {
    return Abs(from->value->x - goal->value->x) + Abs(from->value->y - goal->value->y);
}

float Graph::d(Vertex* v1, Vertex* v2) {
    // return edge weights from v1 to v2
    return v1->neighbourEdgeWeights[v2];
}

int Graph::Abs(int x) {
    if (x < 0) return -x;
    return x;
}

std::vector<Vertex*> Graph::reconstructPath(std::map<Vertex*, Vertex*> cameFrom, Vertex* current) {
    std::vector<Vertex*> path;
    path.insert(path.begin(), current);
    while(cameFrom.find(current) != cameFrom.end()) {
        current = cameFrom[current];
        if (current != nullptr) {
            path.insert(path.begin(), current);
        }
    }
    return path;
}
