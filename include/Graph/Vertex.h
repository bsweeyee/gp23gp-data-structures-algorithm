#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <map>
#include "Vec2.h"

struct Vertex {
    Vec2* value;
    std::vector<Vertex*> neightbours;
    std::map<Vertex*, float> neighbourEdgeWeights; // map of edge weights of neighbours 
    int id;

    Vertex() {
    }

    ~Vertex() {
        delete value;
    }
};

#endif