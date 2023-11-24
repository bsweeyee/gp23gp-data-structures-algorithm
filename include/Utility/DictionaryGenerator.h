#ifndef _DICTIONARYGENERATOR_H_
#define _DICTIONARYGENERATOR_H_

#include <string>
#include <fstream>
#include <sstream>
#include "HashMap/HashMap.h"
#include "Map/Map.h"

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

#endif