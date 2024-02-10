#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <string>
#include "LinkedListEntry.h"

class HashMap {
    public:
        ~HashMap() {
            Dispose();
        }

        void Initialize(int size);
        bool Insert(std::string key, std::string value);
        std::string Lookup(std::string key);
        std::string Remove(std::string key);
        void Dispose();
        LinkedListEntry** entries;
        int size;
    private:
        int HashFunction(std::string key);
};

void HashMap::Initialize(int size) {
    this->size = size;
    entries = new LinkedListEntry*[size];
    for(int i=0; i<size; i++) {
        entries[i] = nullptr;
    }

}

bool HashMap::Insert(std::string key, std::string value) {
    // printf("Inserted (key: %s, value: %s)\n", key.c_str(), value.c_str());
    int hash = HashFunction(key);
    int isCollided = false;    
    if (entries[hash] == nullptr) {
        entries[hash] = new LinkedListEntry(key, value);
    } else { // if hash already exists, we append the entry to the end of the exising hash entry
        if (entries[hash]->key == key) {
            // key already exist, do not add into hashmap
            printf("key already exists: %s\n", key.c_str());
        } else {
            isCollided = true;            
            entries[hash]->Last()->next = new LinkedListEntry(key, value);            
        }
    }
    return isCollided;        
}

std::string HashMap::Lookup(std::string key) {
    int hash = HashFunction(key);
    if (entries[hash] == nullptr) {
        printf("key not found %s\n", key.c_str());
        return "";
    }
    LinkedListEntry* toCheck = entries[hash];
    while(toCheck != nullptr) {
        if (toCheck->key == key) {
            return toCheck->value;
        }
        toCheck = toCheck->next;
    }
    printf("key not found %s\n", key.c_str());
    return "";
}

std::string HashMap::Remove(std::string key) {
    int hash = HashFunction(key);
    std::string found = "";
    if (entries[hash] == nullptr) {
        printf("key not found %s\n", key.c_str());
        return nullptr;
    }
    LinkedListEntry* foundEntry = entries[hash];
    if (foundEntry->key == key) {
        found = entries[hash]->value;
        if (foundEntry->next != nullptr) {
            entries[hash] = foundEntry->next;
        }
        else {
            entries[hash] = nullptr;           
        }        
        delete foundEntry;
    } else {
        LinkedListEntry* e = foundEntry;
        LinkedListEntry* n = foundEntry->next;
        while(e != nullptr) {            
            if (n->key == key) {             
                e->next = n->next;
                found = n->value;
                delete n;
                break;
            }
            e = n;
            if (e != nullptr) {
                n = n->next;
            }
        }
    }
    return found;   
}

int HashMap::HashFunction(std::string key) {
    int hashDigest = 0;
    for (char& c:key) {
        hashDigest += (int)c;
    }
    return hashDigest % size;
}

void HashMap::Dispose() {
    for(int i=0; i<size; i++) {
        LinkedListEntry* e = entries[i];
        while(e != nullptr) {
            LinkedListEntry* n = e->next;
            delete e;
            e = n;
        }
    }
    delete entries;
}

#endif