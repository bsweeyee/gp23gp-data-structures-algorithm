#include <cerrno>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <cstring>
#include "Map/Map.h"
#include "Map/HashMap.h"
#include "Utility/DictionaryGenerator.h"

int main() {
    Map* m = new Map();
    HashMap* hm = new HashMap();
    
    int loaded = -1;    

    printf("--- How to use ---\n");
    printf("Generate Dictionary with \"g <filename> <size>\", (eg. g RandomDictionary.txt 100)\n");
    printf("Generate Lookup File from Dictionary with \"gl <dictionary file> <lookup file>\", (eg. gl RandomDictionary.txt Lookup.txt)\n\n");
    
    printf("Save Dictionary with \"s <filename>\", (eg. s Dictionary.txt)\n\n");
    
    printf("Load Map with \"ldm <filename>\" [default: Dictionary.txt], (eg. ldm RandomDictionary.txt)\n");
    printf("Load HashMap with \"ldh <filename>\" [default: Dictionary.txt], (eg. ldh RandomDictionary.txt)\n\n");
    
    printf("Insert a new key with \"i <key> <value>\", (eg. i key1 value1)\n\n");
    
    printf("Look for a key with \"l <key>\", (eg. l key1)\n");
    printf("Look for multiple keys with \"lm <filename>\", (eg. lm Look.txt)\n\n");
    
    printf("Delete a key with \"d <key>\", (eg. d key1)\n");
    
    printf("-------------------\n");
    while(true) {
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

        if (o[0] == "i") {
            if (loaded < 0) { printf("No files loaded\n"); continue; }            
            else if (loaded == 0) {
                m->Insert(o[1], o[2]);
                printf("Insert success\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), o[2].c_str());
            } else if (loaded == 1) {
                hm->Insert(o[1], o[2]);
                printf("Insert success\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), o[2].c_str());
            }
        } else if (o[0] == "d") {            
            if (loaded < 0) { printf("No files loaded\n"); continue; }
            else if (loaded == 0) {
                std::string removed = m->Remove(o[1]);
                if (removed != "") {
                    printf("Remove success\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), removed.c_str());
                } else {
                    printf("Remove failed\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), removed.c_str());
                }
            } else if (loaded == 1) {
                std::string removed = hm->Remove(o[1]);
                if (removed != "") {
                    printf("Remove success\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), removed.c_str());
                } else {
                    printf("Remove failed\n{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), removed.c_str());
                }
            }
        } else if (o[0] == "l") {
            if (loaded < 0) { printf("No files loaded\n"); continue; }
            else if (loaded == 0) {
                std::string lookup = m->Lookup(o[1]);
                if (lookup != "") {
                    printf("{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), lookup.c_str());
                } 
            } else if (loaded == 1) {
                std::string lookup = hm->Lookup(o[1]);
                if (lookup != "") {
                    printf("{\n   key: %s\n   value: %s\n}\n", o[1].c_str(), lookup.c_str());
                } 
            }
        } else if (o[0] == "lm") {
            std::vector<std::string> sv;
            DictionaryGenerator::DeserializeLookup(o[1], &sv);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            for(std::string s:sv) {
                if (loaded == 0) { 
                    m->Lookup(s);
                }
                else if (loaded == 1) { 
                    hm->Lookup(s);
                }
                else { printf("No files loaded\n"); break; }
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            if (loaded == 0) printf("[map] look up time: %lld ms\n", milliseconds.count()); 
            if (loaded == 1) printf("[hashmap] look up time: %lld ms\n", milliseconds.count());
        } else if (o[0] == "ldm") {
            m->Dispose();
            std::string dictionaryPath = o[1];
            if (dictionaryPath == "") {
                dictionaryPath = "data/Dictionary.txt";
            }
            std::vector<std::string> keys;
            std::vector<std::string> values;
            int n = 0;  
            n = DictionaryGenerator::Deserialize(dictionaryPath, &keys, &values);
            if (n == 0) { continue; }

            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            for(int i=0; i<n;i++) {  
                m->Insert(keys[i], values[i]);
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            
            loaded = 0;
            printf("[map] insert time of size (%i): %lld ms\n", n, milliseconds.count()); 
            
            keys.clear();
            values.clear();
        } else if (o[0] == "ldh") {
            hm->Dispose();
            std::string dictionaryPath = o[1];
            if (dictionaryPath == "") {
                dictionaryPath = "data/Dictionary.txt";
            }

            std::vector<std::string> keys;
            std::vector<std::string> values;
            int n = 0;
            n = DictionaryGenerator::Deserialize(dictionaryPath, &keys, &values);
            hm->Initialize(n);
            if (n == 0) { continue; }

            int collisionCount = 0;
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            for(int i=0; i<n;i++) {        
                bool isCollided = hm->Insert(keys[i], values[i]);        
                if (isCollided) collisionCount += 1;
            }
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            
            loaded = 1;
            printf("[hashmap] insert time of size (%i): %lld ms\n", n, milliseconds.count());
            printf("[hashmap] collision count: %i\n", collisionCount);

            keys.clear();
            values.clear();
        } else if (o[0] == "g") {   
            std::string dictionaryPath = o[1];
            if (dictionaryPath == "") {
                dictionaryPath = "data/RandomDictionary.txt";
            }         
            DictionaryGenerator::SerializeRandom(dictionaryPath, std::stoi(o[2]));
        } else if (o[0] == "gl") {
            std::string dictionaryPath = o[1];
            std::string lookupPath = o[2];
            if (dictionaryPath == "") {
                dictionaryPath = "data/RandomDictionary.txt";
            }
            if (lookupPath == "") {
                lookupPath = "data/Lookup.txt";
            }
            DictionaryGenerator::SerializeLookup(dictionaryPath, lookupPath);                 
        } else if (o[0] == "s") {
            if (loaded < 0) { printf("No files loaded\n"); continue; }
            else if (loaded == 0) {
                DictionaryGenerator::Serialize(o[1], m);
                printf("file saved: %s\n", o[1].c_str());
            } else if (loaded == 1) {
                DictionaryGenerator::Serialize(o[1], hm);
            }
        } else {
            printf("invalid command\n");
        }
        printf("-----\n");
    }
    
    delete m;
    delete hm;
}