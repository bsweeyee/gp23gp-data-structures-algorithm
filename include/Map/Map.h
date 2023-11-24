#ifndef _MAP_H_
#define _MAP_H_

#include "Entry.h"
#include <vector>
#include <stack>
#include <algorithm>

class Map {
    public:
        ~Map() {
            for(Entry* e : entries) {
                delete e;
            }
            entries.clear();
        }

        void Insert(std::string key, std::string value);
        std::string Lookup(std::string key);
        std::string Remove(std::string key);
        void Dispose();
        std::vector<Entry*> entries;    
};

void Map::Insert(std::string key, std::string value) {
    auto iter = std::find_if(entries.begin(), entries.end(), [&] (Entry* e) { return e->key == key; });
    if (iter == entries.end()) {
        entries.push_back(new Entry(key, value));
    } else {
        (*iter)->value = value;
    }
}

std::string Map::Lookup(std::string key) {
    for(Entry* e: entries) {
        if (e->key == key) {
            return e->value;
        }
    }
    printf("key not found: %s\n", key.c_str());
    return "";
}

std::string Map::Remove(std::string key) {
    int idx = -1;
    std::string r = "";
    std::stack<Entry*> temp;
    for(int i=entries.size()-1; i>=0; i--) {
        if (entries[i]->key == key) {
            r = entries[i]->value;
            entries.pop_back();
            while(temp.size() > 0) {
                entries.push_back(temp.top());
                temp.pop();
            }            
            break;
        }
        else {
            temp.push(entries[i]);
            entries.pop_back();
        }
    }

    return r;

    // std::erase_if(entries, [](Entry* x) { return x->key == key; });    
}

void Map::Dispose() {
    for(Entry* e : entries) {
        delete e;
    }
    entries.clear();
}

#endif