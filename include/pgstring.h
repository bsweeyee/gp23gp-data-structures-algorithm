#pragma once
#include <cstring>

class PG_String {
private:
    const int FIXED_BUFFER_SIZE = 2;
    unsigned int m_capacity = FIXED_BUFFER_SIZE;
    unsigned int m_size = 0;
    
    char* m_buffer;
public:    
    PG_String(const char* value) {        
        m_size = strlen(value);
        while (m_size + 1 >= m_capacity) {
            m_capacity *= 2;
        }
        m_buffer = new char[m_capacity];
        // m_buffer = new char[m_size+1] { 0 };
        memcpy(m_buffer, value, m_size);
        m_buffer[m_size] = '\0';                        
    }

    PG_String(const char* lhs, const char* rhs) {        
        int lhs_size = strlen(lhs);
        int rhs_size = strlen(rhs);
        m_size = lhs_size + rhs_size;

        while (m_size + 1 >= m_capacity) {
            m_capacity *= 2;
        }
        m_buffer = new char[m_capacity];
        memcpy(m_buffer, lhs, lhs_size+1);
        strncat(m_buffer, rhs, rhs_size);

        m_buffer[m_size] = '\0';                        
    }

    PG_String(const PG_String& other) 
        : m_size(other.m_size)
    { // this is a copy constructor
        while (m_size + other.m_size + 1 >= m_capacity) {
            m_capacity *= 2;
        }
        m_buffer = new char[m_capacity];
        memcpy(m_buffer, other.m_buffer, m_size + 1);
    }

    ~PG_String() {
        delete[] m_buffer;
    }

    char* c_str() const {
        return m_buffer;
    }

    unsigned int size() const {
        return m_size;
    }

    unsigned int capacity() const {
        return m_capacity;
    }

    bool operator==(const PG_String& other) {
        return (*this) == other.m_buffer; 
    }

    bool operator!=(const PG_String& other) {
        return (*this) != other.m_buffer; 
    }

    bool operator==(const char* other) {        
        return strcmp(m_buffer, other) == 0;
    }

    bool operator!=(const char* other) {
        return strcmp(m_buffer, other) != 0;
    }

    PG_String& operator+=(const PG_String& other) {        
        return (*this) += other.m_buffer;
    }

    PG_String& operator+=(const char* other) {
        int otherSize = strlen(other);
        while (otherSize + m_size + 1 >= m_capacity) {
            m_capacity *= 2;
        }

        char* newBuffer = new char[m_capacity];                
        memcpy(newBuffer, m_buffer, m_size+1);
        strncat(newBuffer, other, otherSize);
        
        m_size += otherSize;
        newBuffer[m_size] = '\0';

        delete[] m_buffer;
        m_buffer = newBuffer;

        return (*this);
    }
};

inline PG_String operator+(const PG_String& lhs, const char* rhs) {                    
    return PG_String(lhs.c_str(), rhs); 
}

inline PG_String operator+(const PG_String& lhs, const PG_String& rhs) {            
    return PG_String(lhs.c_str(), rhs.c_str()); 
}