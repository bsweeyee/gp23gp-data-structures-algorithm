#pragma once
#include <cstdio>

struct CIO {
    static int readFile(const char* filePath, char* buffer) {
        FILE* pFile;
        long lSize;

        pFile = fopen(filePath, "rb");
        if (pFile==NULL) { char b[1]; b[0] = '\0'; return -1; }
        fseek(pFile, 0, SEEK_END);
        lSize = ftell (pFile);
        rewind(pFile);

        fread (buffer,sizeof(char),lSize,pFile);
        buffer[lSize] = '\0';
        fclose(pFile);

        return lSize;
    }

    static void writeFile(const char* filePath, const char* buffer, int bufferLen) {
        FILE* pFile;
        pFile = fopen(filePath, "wb");

        fwrite(buffer, sizeof(char), bufferLen, pFile);
        fclose(pFile);        
    }

    static void appendFile(const char* filePath, const char* buffer, int bufferLen) {
        FILE* pFile;
        pFile = fopen(filePath, "a+b");

        fwrite(buffer, sizeof(char), bufferLen, pFile);
        fclose(pFile);
    }
};