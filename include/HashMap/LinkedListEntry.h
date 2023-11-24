#ifndef _LINKEDLISTENTRY_H_
#define _LINKEDLISTENTRY_H_

#include <vector>
#include <string>

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

#endif