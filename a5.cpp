#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <chrono>
#include <fstream>

using namespace std;
struct Entry {
    std::string key;
    std::string value;

    Entry(std::string k, std::string v) {
        key = k;
        value = v;
    }
};

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
        void Remove(std::string key);
    private:
        std::vector<Entry*> entries;
};

void Map::Insert(std::string key, std::string value) {
    entries.push_back(new Entry(key, value));
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

void Map::Remove(std::string key) {
    int idx = -1;
    std::stack<Entry*> temp;
    for(int i=entries.size()-1; i>=0; i--) {
        if (entries[i]->key == key) {
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

    // std::erase_if(entries, [](Entry* x) { return x->key == key; });    
}

struct LinkedListEntry {
    std::string key;
    std::string value;
    LinkedListEntry(std::string k, std::string v) {
        key = k;
        value = v;
        next = nullptr;
    }
    LinkedListEntry* next;
    LinkedListEntry* Last() {
        if (next == nullptr) return this;
        LinkedListEntry* last = next;
        while (last->next != nullptr) {
            last = last->next;
        }
        return last;
    }
};

class HashMap {
    public:
        void Initialize(int size);
        void Insert(std::string key, std::string value);
        std::string Lookup(std::string key);
        void Remove(std::string key);
    private:
        int HashFunction(std::string key);
        int size;
        LinkedListEntry** entries;
};

void HashMap::Initialize(int size) {
    this->size = size;
    entries = new LinkedListEntry*[size];
    for(int i=0; i<size; i++) {
        entries[i] = nullptr;
    }
}

void HashMap::Insert(std::string key, std::string value) {
    // printf("Inserted (key: %s, value: %s)\n", key.c_str(), value.c_str());
    int hash = HashFunction(key);
    if (entries[hash] == nullptr) {
        entries[hash] = new LinkedListEntry(key, value);
    } else { // if hash already exists, we append the entry to the end of the exising hash entry
        if (entries[hash]->key == key) {
            // key already exist, do not add into hashmap
            printf("key already exists: %s\n", key.c_str());
        } else {
            entries[hash]->Last()->next = new LinkedListEntry(key, value);
        }
    }
}

std::string HashMap::Lookup(std::string key) {
    int hash = HashFunction(key);
    if (entries[hash] == nullptr) {
        printf("key not found %s\n", key.c_str());
        return nullptr;
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

int HashMap::HashFunction(std::string key) {
    int hashDigest = 0;
    for (char& c:key) {
        hashDigest += (int)c;
    }
    return hashDigest % size;
}

std::string gen_random(int len) {
    char alphanum[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main() {

    // std::string line;
    // std::ifstream myfile("Dictionary.txt");

    // if (myfile.is_open()) {
    //     while ( getline (myfile, line) ) {
    //         // std::string tokens[2];
    //         // while(getline(line, tokens, ":")) {

    //         // }
    //     }
    //     myfile.close();
    // } else {
    //     printf("Unable to open file\n");
    //     return 0;
    // }

    // generate random strings here
    int n = 99999;
    vector<std::string> keys;
    vector<std::string> values;

    for(int i=0; i<n; i++) {
        keys.push_back(gen_random(5));
        values.push_back(gen_random(10));
    }

    Map* m = new Map();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i=0; i<n;i++) {  
        m->Insert(keys[i], values[i]);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    printf("[map] insert time of size (%i): %lld ms\n", n, milliseconds.count());

    // std::string s = m->Lookup("k1");
    // printf("look up 1: %s\n", s.c_str());
    
    // m->Remove("k1");
    // s = m->Lookup("k1");
    // s = m->Lookup("k2");
    // printf("look up 2: %s\n", s.c_str());    

    HashMap* hm = new HashMap();
    hm->Initialize(99999);
    begin = std::chrono::steady_clock::now();
    for(int i=0; i<n;i++) {        
        hm->Insert(keys[i], values[i]);        
    }
    end = std::chrono::steady_clock::now();
    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    printf("[hashmap] insert time of size (%i): %lld ms\n", n, milliseconds.count());
    
    delete m;
    delete hm;
}