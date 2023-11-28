#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <map>
#include "Sort/Sort.h"

using namespace std;

static const int INTEGERS = 65535;    

int binary_search_recursive(int value, int* array, int min, int max) {
    int mid = (max + min) / 2;    
    if (min == mid || max == mid) {
        if (value != array[mid]) {
            return -1;
        }
    }
    else if (value > array[mid]) {
        return binary_search_recursive(value, array, mid, max);
    } else if (value < array[mid]) {
        return binary_search_recursive(value, array, 0, mid);
    }
    return mid;   
}

int binary_search_loop(int value, int* array, int min, int max) {
    while(true) {
        int mid = (max + min) / 2;        
        if (max == mid || min == mid) {
            if (value != array[mid]) {
                return -1;
            } else {
                return mid;
            }
        }
        else if (value > array[mid]) {
            min = mid;
        } else if(value < array[mid]) {
            max = mid;
        } else {
            if (value != array[mid]) {
                return -1;
            } else {
                return mid;
            }
        }
    }
}

bool validateSorted(int* array, int length) {
    for(int i=0; i<length - 1; i++) {
        if (array[i] > array[i+1]) {
            // printf("(%i: %i), (%i: %i)\n", i, array[i], i, array[i+1]);
            return false;
        }
    }
    return true;
}

void print_array(std::string beforeText, int* array, int length) {
    printf("---- %s (Sort validated: %d) ----\n", beforeText.c_str(), validateSorted(array, length));    

    if (length > 10) return;
    for(int i=0; i<length; i++) {
        printf("(%i: %i),", i, array[i]);
    }    
    printf("\n");
}

void reassign(int* array, int* target, int length) {    
    for(int i=0; i<length; i++) {
        target[i] = array[i];
    }    
}

void saveCSV(std::string fileName, std::map<std::string, std::string> columns, long long time) {
    std::ifstream infile("stats/" + fileName + ".csv");
    int index = 0;
    if (!infile.is_open()) {        
        std::ofstream outfile("stats/" + fileName + ".csv", std::ofstream::out);        
        if (outfile.is_open()) {
            outfile << "ID,";
            for(const auto &k : columns) {
                outfile << k.first;
                outfile << ",";                
            }
            outfile << "Time\n";                                    
            index += 1;
        }
        outfile.close();
    } else {
        std::string line;
        while ( getline (infile, line) ) {
            index += 1;
        }
    }
    infile.close();

    std::ofstream outfile("stats/" + fileName + ".csv", std::ios::app);
    if (outfile.is_open()) {                
        outfile << index;
        outfile << ",";
        for(const auto &k : columns) {
            outfile << k.second;
            outfile << ",";                
        }
        outfile << time;
        outfile << "\n";
    }
    outfile.close();
}

void runSort(std::string type, int* array, int* sortedArray, int n) {
    if (type == "es") {
        print_array("Before sort", array, n);                            
                                                    
        reassign(array, sortedArray, n);
        sortedArray = Sort::exchange_sort(sortedArray, n);                            

        print_array("After sort", sortedArray, n);
    } else if (type == "ss") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::selection_sort(sortedArray, n);
        
        print_array("After sort", sortedArray, n);
    } else if (type == "bs") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::bubble_sort(sortedArray, n);
        
        print_array("After sort", sortedArray, n);
    } else if (type == "is") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::insertion_sort(sortedArray, n);
        
        print_array("After sort", sortedArray, n);
    } else if (type == "qs") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::quick_sort(sortedArray, 0, n-1);

        print_array("After sort", sortedArray, n);
    } else if (type == "ms") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::merge_sort(sortedArray, 0, n-1);

        print_array("After sort", sortedArray, n);
    } else if (type == "cs") {
        print_array("Before sort", array, n);

        reassign(array, sortedArray, n);
        sortedArray = Sort::counting_sort(sortedArray, n, INTEGERS);
        
        print_array("After sort", sortedArray, n);
    }
}

void runSearch(std::string type, std::string searchValue, int* array, int* sortedArray, int n) {
    if (type == "bsr") {
        int index = binary_search_recursive(std::stoi(searchValue), sortedArray, 0, n);
        if (index >= 0) {
            printf("found at index: %i\n", index);
        }
        else {
            printf("%s not found in array\n", searchValue.c_str());
        }
    } else if (type == "bsl") {
        int index = binary_search_loop(std::stoi(searchValue), sortedArray, 0, n);
        if (index >= 0) {
            printf("found at index: %i\n", index);
        }
        else {
            printf("%s not found in array\n", searchValue.c_str());
        }
    }        
}

int main() {
    printf("--- How to use ---\n");
    printf("Generate Random integers: \"gr <filename> <size>\", (eg. g Integers.txt 100)\n");    
    printf("Generate Sort Random integers: \"grs <filename> <size>\", (eg. g Integers.txt 100)\n");        
    printf("Load Sort integers: \"l <filename>\", (eg. l Integers.txt)\n");
    printf("Randomise data set each cycle: \"r <size>\", (eg. r 50)\n");
    printf("Randomise sorted data set each cycle: \"rs <size>\", (eg. rs 50)\n");   
    printf("-------------------\n");

    // initialize list of random int from 0-1000    
    srand(time(NULL));

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

        bool alwaysRandomise = false;
        bool isLoaded = false;
        int size = 0;
        int randomType = 0;        

        // apply sort        
        if (o[0] == "gr") {
            std::ofstream myfile (o[1]);
            int n = std::stoi(o[2]);           

            // generate random strings
            if (myfile.is_open()) {                
                myfile << n; // first value in line is always size of integers 
                myfile << "\n";
                for(int i=0; i<n; i++) {
                    int value = std::rand() % INTEGERS;                
                    myfile << value;
                    myfile << "\n";                
                }
                myfile.close();
            }
        } else if (o[0] == "grs") {
            std::ofstream myfile (o[1]);
            int n = std::stoi(o[2]);
            int* tempArray = new int[n];

            for(int i=0; i<n; i++) {
                tempArray[i] = std::rand() % INTEGERS;
            }
            tempArray = Sort::counting_sort(tempArray, n, INTEGERS);

            if (myfile.is_open()) {                
                myfile << n; // first value in line is always size of integers 
                myfile << "\n";
                for(int i=0; i<n; i++) {
                    myfile << tempArray[i];
                    myfile << "\n";                                                    
                }
                myfile.close();
            }            

            delete[] tempArray;
        } else if (o[0] == "r") {
            alwaysRandomise = true;
            isLoaded = true;
            size = std::stoi(o[1]);
            randomType = 0;            
        } else if (o[0] == "rs") {
            alwaysRandomise = true;
            isLoaded = true;
            size = std::stoi(o[1]);
            randomType = 1;
        } else if (o[0] == "l") {
            isLoaded = true;
        }
        if (isLoaded) {
            if (!alwaysRandomise) {  
                int n = 0;                                  
                std::string line;
                std::string fileName = o[1];            
                std::ifstream myfile(fileName);
                
                bool isFailOpenFile = false;
                if (myfile.is_open()) {
                    getline (myfile, line);
                    n = std::stoi(line);
                } else {
                    printf("Unable to open file\n");
                    isFailOpenFile = true;
                }               

                if (!isFailOpenFile) {
                    int array[n];
                    int* sortedArray = new int[n];
                    
                    if (myfile.is_open()) {                                
                        int i = 0;
                        while ( getline (myfile, line) ) {                    
                            array[i] = std::stoi(line);
                            i += 1;                                            
                        }
                        myfile.close();
                    }                 

                    printf("--- How to use ---\n");
                    printf("Unload file: \"ul\"\n");
                    printf("Exchange sort: \"es <optional: repetition> \"\n");
                    printf("Selection sort: \"ss <optional: repetition>\"\n");
                    printf("Bubble sort: \"bs <optional: repetition>\"\n");
                    printf("Insertion sort: \"is <optional: repetition>\"\n");
                    printf("Counting sort: \"cs <optional: repetition>\"\n");
                    printf("Quick sort: \"qs <optional: repetition>\"\n");
                    printf("Merge sort: \"ms <optional: repetition>\"\n");
                    printf("Heap sort: \"hs <optional: repetition>\"\n");
                    printf("Binary search (recursive): \"bsr <value>\"\n");
                    printf("Binary search (loop): \"bsl <value>\"\n");
                    printf("-------------------\n"); 

                    while (isLoaded) {
                        printf(">> ");
            
                        std::string command;
                        std::getline(std::cin, command);

                        std::stringstream ss(command);
                        std::string s;
                        std::string o[3] { "", "", "" };
                        int i = 0;
                        while (std::getline(ss, s, ' ')) {
                            o[i] = s;
                            i += 1;
                        }

                        if (o[0] == "ul") { isLoaded = false; break; }
                        // if (o[1].empty()) { // default to 1 if no additional input
                        //     o[1] = 1;                                            
                        // }
                        int reps = std::stoi(o[1]);
                        while(reps > 0) {                        
                            reps -= 1;
                            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();    
                            
                            runSort(o[0], array, sortedArray, n);
                            runSearch(o[0], o[1], array, sortedArray, n);

                            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                            auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                            printf("[%s] time: %lld us\n", o[0].c_str(), time.count());
                            
                            std::string suffix = ".txt";
                            std::string prefix = "data/";
                            int len = fileName.length();
                                                                            
                            std::map<std::string, std::string> m;
                            m["SortType"] = o[0];
                            m["Range"] = fileName.substr(prefix.length(), len - suffix.length() - prefix.length());

                            saveCSV("sort_data", m, time.count());
                        }                    
                    }
                    delete[] sortedArray;
                }
            } else {
                printf("--- How to use ---\n");
                printf("Unload file: \"ul\"\n");
                printf("Exchange sort: \"es <optional: repetition> \"\n");
                printf("Selection sort: \"ss <optional: repetition>\"\n");
                printf("Bubble sort: \"bs <optional: repetition>\"\n");
                printf("Insertion sort: \"is <optional: repetition>\"\n");
                printf("Counting sort: \"cs <optional: repetition>\"\n");
                printf("Quick sort: \"qs <optional: repetition>\"\n");
                printf("Merge sort: \"ms <optional: repetition>\"\n");
                printf("Heap sort: \"hs <optional: repetition>\"\n");
                printf("Binary search (recursive): \"bsr <value>\"\n");
                printf("Binary search (loop): \"bsl <value>\"\n");
                printf("-------------------\n"); 

                while (isLoaded) {
                    printf(">> ");

                    int array[size];                    
                    int* sortedArray = new int[size];
        
                    std::string command;
                    std::getline(std::cin, command);

                    std::stringstream ss(command);
                    std::string s;
                    std::string o[3] { "", "", "" };
                    int i = 0;
                    while (std::getline(ss, s, ' ')) {
                        o[i] = s;
                        i += 1;
                    }

                    if (o[0] == "ul") { isLoaded = false; break; }
                    // if (o[1].empty()) { // default to 1 if no additional input
                    //     o[1] = 1;                                            
                    // }
                    int reps = std::stoi(o[1]);
                    while(reps > 0) {                        
                        reps -= 1;
                        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();    
                        
                        for(int i=0; i<size; i++) {
                            array[i] = std::rand() % INTEGERS;
                        }
                        if (randomType == 1) {
                            Sort::counting_sort(array, size, INTEGERS);
                        }
                        runSort(o[0], array, sortedArray, size);
                        runSearch(o[0], o[1], array, sortedArray, size);

                        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
                        printf("[%s] time: %lld us\n", o[0].c_str(), time.count());
                        
                        std::string suffix = ".txt";
                        std::string prefix = "data/";                        
                                                                        
                        std::map<std::string, std::string> m;
                        m["SortType"] = o[0];
                        m["Range"] = "RandomGenerateInt" + std::to_string(size);

                        saveCSV("sort_data", m, time.count());
                    }                    
                    delete[] sortedArray;
                }
            }
            printf("--- How to use ---\n");
            printf("Generate Sort integers: \"g <filename> <size>\", (eg. g Integers.txt 100)\n");    
            printf("Load Sort integers: \"l <filename>\", (eg. l Integers.txt)\n");
            printf("Randomise data set each cycle: \"r <size>\", (eg. r 50)\n");
            printf("Randomise sorted data set each cycle: \"rs <size>\", (eg. rs 50)\n");    
            printf("-------------------\n"); 
        }         
    }        

}