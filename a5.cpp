#include <cerrno>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cstring>

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
        entries[hash]->next = nullptr;
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

class DictionaryGenerator {
    private:
        static std::string gen_random(int len) {
            char alphanum[] = "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            std::string tmp_s;
            tmp_s.reserve(len);
            for (int i = 0; i < len; ++i) {
                tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
            }

            return tmp_s;
        };
    public:
        static void SerializeRandom(std::string filePath, int len) {
            std::ofstream myfile (filePath);
            srand(time(NULL));
            
            // generate random strings
            if (myfile.is_open()) {                
                for(int i=0; i<len; i++) {                
                    std::string input = gen_random(5) + ":" + gen_random(10) + "\n";
                    myfile << input;                
                }
                myfile.close();
            }
        };

        static void Serialize(std::string filePath, Map* map) {
            std::ofstream myfile(filePath);
            if (myfile.is_open()) {
                for(Entry* e: map->entries) {
                    std::string input = e->key + ":" + e->value + "\n";
                    myfile << input;                                        
                }
                myfile.close();
            }
        };

        static void Serialize(std::string filePath, HashMap* map) {
            std::ofstream myfile(filePath);
            if (myfile.is_open()) {
                for(int i=0; i<map->size; i++) {
                    LinkedListEntry* e = map->entries[i];
                    while(e != nullptr) {
                        std::string input = e->key + ":" + e->value + "\n";
                        myfile << input;                                        
                        e = e->next;
                    }
                }
                myfile.close();
            }
        };

        static int Deserialize(std::string filePath, std::vector<std::string>* keys, std::vector<std::string>* values) {
            int n = 0;
            std::string line;
            std::ifstream myfile(filePath);

            if (myfile.is_open()) {
                while ( getline (myfile, line) ) {
                    std::stringstream ss(line);
                    std::string s;
                    std::string o[2];
                    int i = 0;
                    while (std::getline(ss, s, ':')) {
                        o[i] = s;
                        i++;
                    }
                    n++;
                    keys->push_back(o[0]);
                    values->push_back(o[1]);                        
                }
                myfile.close();
            } else {
                printf("Unable to open file\n");
                return 0;
            }
            return n;
        }; 

        static void SerializeLookup(std::string dictionaryPath, std::string lookupPath) {            
            std::string line;
            std::ifstream myfile(dictionaryPath);
            std::vector<std::string> keys;
            if (myfile.is_open()) {
                while(getline (myfile, line)) {
                    std::stringstream ss(line);
                    std::string s;                    
                    int i = 0;
                    while (std::getline(ss, s, ':')) {
                        if (i == 0) { keys.push_back(s); }
                        i++;
                    }
                }
                myfile.close();
            }
            std::ofstream outfile(lookupPath);
            if (outfile.is_open()) {
                for(std::string s:keys) {
                    outfile << (s + "\n");
                }
                outfile.close();
            }
        }

        static void DeserializeLookup(std::string filePath, std::vector<std::string>* lookup) {
            std::string line;
            std::ifstream myfile(filePath);
            if (myfile.is_open()) {
                while(getline (myfile, line)) {
                    lookup->push_back(line);
                }
                myfile.close();
            }
        }       
};

int main() {
    Map* m = new Map();
    HashMap* hm = new HashMap();
    
    int loaded = -1;    

    printf("--- How to use ---\n");
    printf("Save Dictionary with \"s <filename>\", (eg. s Dictionary.txt)\n");
    printf("Load Map with \"ldm <filename>\" [default: Dictionary.txt], (eg. ldm RandomDictionary.txt)\n");
    printf("Load HashMap with \"ldh <filename>\" [default: Dictionary.txt], (eg. ldh RandomDictionary.txt)\n");
    printf("Generate Dictionary with \"g <filename> <size>\", (eg. g RandomDictionary.txt 100)\n");
    printf("Generate Lookup File from Dictionary with \"gl <dictionary file> <lookup file>\", (eg. gl RandomDictionary.txt Lookup.txt)\n");
    printf("Insert a new key with \"i <key> <value>\", (eg. i key1 value1)\n");
    printf("Look for a key with \"l <key>\", (eg. l key1)\n");
    printf("Look for multiple keys with \"lm <filename>\", (eg. lm Look.txt)\n");
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
                dictionaryPath = "Dictionary.txt";
            }
            std::vector<std::string> keys;
            std::vector<std::string> values;  
            int n = DictionaryGenerator::Deserialize(dictionaryPath, &keys, &values);
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
                dictionaryPath = "Dictionary.txt";
            }

            std::vector<std::string> keys;
            std::vector<std::string> values;
            int n = DictionaryGenerator::Deserialize(dictionaryPath, &keys, &values);
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
                dictionaryPath = "RandomDictionary.txt";
            }         
            DictionaryGenerator::SerializeRandom(dictionaryPath, std::stoi(o[2]));
        } else if (o[0] == "gl") {
            std::string dictionaryPath = o[1];
            std::string lookupPath = o[2];
            if (dictionaryPath == "") {
                dictionaryPath = "RandomDictionary.txt";
            }
            if (lookupPath == "") {
                lookupPath = "Lookup.txt";
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