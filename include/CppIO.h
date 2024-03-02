#ifndef _CPPIO_H_
#define _CPPIO_H_

#include <fstream>
#include <ostream>
#include <string>
#include <sstream>

namespace CPP_IO {     
    std::string ReadTextFile(std::string filePath) {
        std::string line;
        std::ifstream myfile(filePath);
        std::stringstream stream;
        try {
            if (myfile.is_open()) {
                stream << myfile.rdbuf();
            }
            myfile.close();
        }
        catch(std::ifstream::failure e) {
            printf("ERROR %s: Failed to read filename %s", e.what(), filePath.c_str());
        }
        return stream.str();
    }

    void WriteToTextFile(std::string filePath, std::string output) {        
        std::ofstream outfile(filePath, std::ofstream::out);                
        try {
            if (outfile.is_open()) {
                outfile << output;
            }
            outfile.close();        
        }
        catch(std::ofstream::failure e) {
            printf("ERROR %s: Failed to read filename %s", e.what(), filePath.c_str());
        }
    }

    void AppendToTextFile(std::string filePath, std::string output) {
        std::ifstream infile(filePath);
        if (!infile.is_open()) {
            WriteToTextFile(filePath, output);
        } else {
            std::ofstream outfile(filePath, std::ios::app);
            if (outfile.is_open()) {
                outfile << output;
            }
            outfile.close();
        }        
    }
}

#endif