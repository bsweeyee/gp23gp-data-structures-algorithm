#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <chrono>
#include "Graph/Grid.h"

void saveCSV(std::string fileName, std::map<std::string, std::string> columns, long long time) {
    std::ifstream infile("stats/" + fileName + ".csv");
    int index = 0;
    if (!infile.is_open()) {        
        std::ofstream outfile("stats/" + fileName + ".csv", std::ofstream::out);        
        if (outfile.is_open()) {
            outfile << "ID,";
            for(const auto &k : columns) {
                outfile << k.first;
                outfile << ",";                
            }
            outfile << "Time\n";                                    
            index += 1;
        }
        outfile.close();
    } else {
        std::string line;
        while ( getline (infile, line) ) {
            index += 1;
        }
    }
    infile.close();

    std::ofstream outfile("stats/" + fileName + ".csv", std::ios::app);
    if (outfile.is_open()) {                
        outfile << index;
        outfile << ",";
        for(const auto &k : columns) {
            outfile << k.second;
            outfile << ",";                
        }
        outfile << time;
        outfile << "\n";
    }
    outfile.close();
}

int main() {
    srand(time(NULL));

    // randomly pick a start and end vertex
    int startVertexIdx = -1;
    int endVertexIdx = -1;   

    while (true) {
        printf("--- How to use ---\n");            
        printf("Load Graph Nodes: \"l <filename>\", (eg. l GraphNodes.txt)\n");       
        printf("-------------------\n");
        
        Grid* grid = new Grid();
        
        printf(">> ");
    
        std::string command;
        std::getline(std::cin, command);

        std::stringstream ss(command);
        std::string s;
        std::string o[3];
        int i = 0;
        while (std::getline(ss, s, ' ')) {
            o[i] = s;
            i += 1;
        }

        std::string line;
        std::ifstream myfile(o[1]);
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
                    else if (c == 'S') {
                        v->value = new Vec2(x, y);
                        v->id = idx;
                        grid->vertexList.push_back(v);
                        startVertexIdx = idx;
                        idx += 1;
                    } else if (c == 'G') {
                        v->value = new Vec2(x, y);
                        v->id = idx;
                        grid->vertexList.push_back(v);
                        endVertexIdx = idx;
                        idx += 1;
                    }
                    x += 1;
                }
                if (x > grid->size->x) {
                    grid->size->x = x;
                }
                x = 0;
                y += 1;
            }
            grid->size->y = y;
            myfile.close();
        }
        else { 
            printf("Unable to open file\n");
            continue;
        }
        
        int n = grid->vertexList.size();  

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

        // randomly pick a start and end vertex ( if none is loaded )
        if (startVertexIdx < 0) startVertexIdx = rand() % grid->vertexList.size();
        if (endVertexIdx < 0) endVertexIdx = rand() % grid->vertexList.size();   

        // grid->PrintVertices();
        // grid->PrintNeighbours();
        grid->PrettyPrint();
        printf("\n");

        bool isExit = false;
        while(!isExit) {
            printf("--- How to use ---\n");
            printf("Unload current graph file: ul\n");           
            printf("Breadth First Search (recursive): bfsr <repetition count> <pretty print: yes - 1, no - 0 (default)>\n");
            printf("Depth First Search (recursive): dfsr <repetition count> <pretty print: yes - 1, no - 0 (default)>\n");
            printf("Breadth First Search (loop): bfsl <repetition count> <pretty print: yes - 1, no - 0 (default)>\n");
            printf("Depth First Search (loop): dfsl <repetition count> <pretty print: yes - 1, no - 0 (default)>\n");
            printf("AStar Search: ats <repetition> <pretty print: yes - 1, no - 0 (default)>\n");
            printf("-------------------\n");

            printf(">> ");
            std::string command;
            std::getline(std::cin, command);

            std::stringstream ss(command);
            std::string s;
            std::string o[3];
            o[2] = "0";
            
            int i = 0;
            while (std::getline(ss, s, ' ')) {
                o[i] = s;
                i += 1;
            }    

            int count = 1;
            int currentCount = 0;                            
            
            if (o[0] == "ats") {
                int repetition = std::stoi(o[1]);
                
                std::vector<Vertex*> path;
                while (repetition > 0) { 
                    path.clear();
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    
                    path = grid->Astar(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx]);
                    
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                    printf("[%s] time: %lld us\n", o[0].c_str(), time.count());

                    std::string suffix = ".txt";
                    std::string prefix = "data/";
                                                                    
                    std::map<std::string, std::string> m;
                    m["SearchType"] = o[0];

                    saveCSV("graph_data", m, time.count());
                    repetition -= 1;
                }

                if(std::stoi(o[2]) == 1) {
                    std::vector<Vertex*> temp;
                    int idx = 0;
                    do {
                        temp.push_back(path[idx]);
                        grid->PrettyPrint(temp, path[path.size()-1]);
                        idx += 1;                        
                        std::cin.ignore();            
                    } while(temp.size() < path.size());
                }
            } else if (o[0] == "dfsl") {
                int repetition = std::stoi(o[1]);
                std::vector<Vertex*> path;
                std::map<Vertex*, bool> discoveredMap;

                while (repetition > 0) { 
                    path.clear();                   
                    for(Vertex* v:grid->vertexList) {
                        discoveredMap[v] = false;
                    }
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();                
                    
                    path = Graph::DFS(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx], path, discoveredMap);
                    
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                    printf("[%s] time: %lld us\n", o[0].c_str(), time.count());

                    std::string suffix = ".txt";
                    std::string prefix = "data/";
                                                                    
                    std::map<std::string, std::string> m;
                    m["SearchType"] = o[0];

                    saveCSV("graph_data", m, time.count());
                    repetition -= 1;
                }
                
                if(std::stoi(o[2]) == 1) {
                    std::vector<Vertex*> temp;
                    int idx = 0;
                    do {
                        temp.push_back(path[idx]);
                        grid->PrettyPrint(temp, path[path.size()-1]);
                        idx += 1;                        
                        std::cin.ignore();            
                    } while(temp.size() < path.size());
                }
            } else if (o[0] == "bfsl") {
                int repetition = std::stoi(o[1]);
                std::vector<Vertex*> path;
                std::map<Vertex*, bool> discoveredMap;
                
                while (repetition > 0) {
                    path.clear();   
                    for(Vertex* v:grid->vertexList) {
                        discoveredMap[v] = false;
                    }
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                    path = Graph::BFS(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx], path, discoveredMap);
                    
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                    printf("[%s] time: %lld us\n", o[0].c_str(), time.count());

                    std::string suffix = ".txt";
                    std::string prefix = "data/";
                                                                    
                    std::map<std::string, std::string> m;
                    m["SearchType"] = o[0];

                    saveCSV("graph_data", m, time.count());
                    
                    repetition -= 1;
                }
                
                if(std::stoi(o[2]) == 1) {
                    std::vector<Vertex*> temp;
                    int idx = 0;
                    do {
                        temp.push_back(path[idx]);
                        grid->PrettyPrint(temp, path[path.size()-1]);
                        idx += 1;                        
                        std::cin.ignore();            
                    } while(temp.size() < path.size());
                }
            } else if (o[0] == "bfsr") {
                int repetition = std::stoi(o[1]);
                std::vector<Vertex*> visited;
                std::vector<Vertex*> unvisited;

                while (repetition > 0) {
                    visited.clear();
                    unvisited.clear();
                    
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                    visited = Graph::BFSReursive(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx], visited, unvisited);
                    
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                    printf("[%s] time: %lld us\n", o[0].c_str(), time.count());

                    std::string suffix = ".txt";
                    std::string prefix = "data/";
                                                                    
                    std::map<std::string, std::string> m;
                    m["SearchType"] = o[0];

                    saveCSV("graph_data", m, time.count());
                    
                    repetition -= 1;                    
                }

                if(std::stoi(o[2]) == 1) {
                    std::vector<Vertex*> temp;
                    int idx = 0;
                    do {
                        temp.push_back(visited[idx]);
                        grid->PrettyPrint(temp, visited[visited.size()-1]);
                        idx += 1;                        
                        std::cin.ignore();            
                    } while(temp.size() < visited.size());
                }
            } else if (o[0] == "dfsr") {
                int repetition = std::stoi(o[1]);
                std::vector<Vertex*> dfoList;
                while (repetition > 0) {
                    dfoList.clear();

                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    
                    dfoList = Graph::DFSRecursive(grid->vertexList[startVertexIdx], grid->vertexList[endVertexIdx], dfoList);
                    
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                    printf("[%s] time: %lld us\n", o[0].c_str(), time.count());

                    std::string suffix = ".txt";
                    std::string prefix = "data/";
                                                                    
                    std::map<std::string, std::string> m;
                    m["SearchType"] = o[0];

                    saveCSV("graph_data", m, time.count());

                    repetition -= 1;                    
                }
                
                if(std::stoi(o[2]) == 1) {
                    std::vector<Vertex*> temp;
                    int idx = 0;
                    do {
                        temp.push_back(dfoList[idx]);
                        grid->PrettyPrint(temp, dfoList[dfoList.size()-1]);
                        idx += 1;                        
                        std::cin.ignore();            
                    } while(temp.size() < dfoList.size());
                }
            } else if (o[0] == "ul") {
                isExit = true;
            }
            else {
                printf("not a valid traversal option");
            }
        }
        delete grid;
    } 
}