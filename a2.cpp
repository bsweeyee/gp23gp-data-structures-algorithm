#include <iostream>
#include <chrono>

using namespace std;

int* exchange_sort(int* array, int length) {
    for (int i=0; i<length; i++) {
        for(int j=i+1; j<length; j++) {
            if (array[j] < array[i]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }    
    return array;
}

int* selection_sort(int* array, int length) {
    for(int i=0; i<length; i++) {
        int lowestIndex = i;
        for (int j=i + 1; j<length; j++) {
            if (array[lowestIndex] > array[j]) {
                lowestIndex = j;                
            }
        }
        if (array[i] != array[lowestIndex]) {
            int temp = array[i];
            array[i] = array[lowestIndex];
            array[lowestIndex] = temp;
        }
    }
    return array;
}

int* bubble_sort(int* array, int length) {     
    for(int i=0; i<length; i++) {        
        for(int j=0; j<length - i - 1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;                
            }
        }
    }
    return array;
}

int* insertion_sort(int* array, int length) {    
    for(int i=1; i<length; i++) { // we start from 1 because insertion sort assumes first item to be sorted        
        for(int j=0; j<i; j++) {
            if (array[i] < array[j]) {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        } 
    }
    return array;
}

int partition(int* array, int left, int right) {
    // pick pivot by using mid point
    int pivotIdx = (right + left)/2;
    int pivot = array[pivotIdx];
    // move pivot to end of array ( to keep it out of the sorting procedure because it will be placed in the correct position at the end)
    int temp = array[pivotIdx];
    array[pivotIdx] = array[right];
    array[right] = temp;

    // we track a left index holding smallest value compared to pivot and right index holding a value greater than pivot
    int tempLeftIdx = 0;
    int tempRightIdx = right - 1;
    
    // now we sort everything according to the value of the current pivotIdx
    while (tempLeftIdx < tempRightIdx) {        
        while(tempLeftIdx <= tempRightIdx && array[tempLeftIdx] <= pivot) {
            tempLeftIdx += 1;
        }
        while(tempLeftIdx <= tempRightIdx && array[tempRightIdx] >= pivot) {
            tempRightIdx -= 1;
        }
        if (tempLeftIdx < tempRightIdx) {
            int temp = array[tempLeftIdx];
            array[tempLeftIdx] = array[tempRightIdx];
            array[tempRightIdx] = temp;

            // for(int j=0; j<10; j++) {
            //     printf("(%i: %i),", j, array[j]);
            // }
            // printf("[swapped indices: %i, %i]\n", tempLeftIdx, tempRightIdx); 
        }        
    }
    // then, we swap back the pivot to the smallest value ( on the left )
    temp = array[right];
    array[right] = array[tempLeftIdx];
    array[tempLeftIdx] = temp;
    // for(int j=0; j<10; j++) {
    //     printf("(%i: %i),", j, array[j]);
    // }
    // printf("[returned pivot indices: %i, %i, %i]\n", pivotIdx, tempLeftIdx, right); 

    return tempLeftIdx; // we return tempLeftIndex because that is the new pivot index 
}

// TODO: implement partition with loop

int* quick_sort(int* array, int left, int right) {
    if (left < right) {
        int partitionIdx = partition(array, left, right);
        array = quick_sort(array, left, partitionIdx-1);
        array = quick_sort(array, partitionIdx+1, right);
    }
    return array;
}

// TODO: implement merge sort

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

void printArray(int* array, int length) {
    for(int i=0; i<length; i++) {
        printf("(%i: %i),", i, array[i]);
    }    
    printf("\n");
}

int main() {
    // initialize list of random int from 0-1000
    srand(time(NULL));
    int n = 10;
    int* array = new int[n];        
    for(int i=0; i<n; i++) {
        array[i] = std::rand() % 1000;
    }    

    if (n <= 10) {
        printf("---- Before sort ----\n");
        printArray(array, n);    
    }

    // apply sort
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // int* sortedArray = exchange_sort(array, n);
    // int* sortedArray = selection_sort(array, n);
    // int* sortedArray = bubble_sort(array, n);
    // int* sortedArray = insertion_sort(array, n);
    int* sortedArray = quick_sort(array, 0, n-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    printf("sort time: %lu ms\n", milliseconds.count());

    // print
    if (n <= 10) {
        printf("---- After sort ----\n");
        printArray(array, n);
    }

    int number;
    cout << "Enter number to find: ";
    cin >> number;

    begin = std::chrono::steady_clock::now();
    int index = binary_search_recursive(number, sortedArray, 0, n);
    // int index = binary_search_loop(number, sortedArray, 0, n);
    end = std::chrono::steady_clock::now();
    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    printf("search time: %lu ms\n", milliseconds.count());

    if (index >= 0) {
        printf("found at index: %i\n", index);
    }
    else {
        printf("%i not found in array\n", number);
    }

    delete[] array;    
}