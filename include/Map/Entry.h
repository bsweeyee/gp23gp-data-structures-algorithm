#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <string>

struct Entry {
    std::string key;
    std::string value;

    Entry(std::string k, std::string v) {
        key = k;
        value = v;
    }
};

#endif