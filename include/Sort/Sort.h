namespace Sort {
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

    int partitionHoare(int* array, int left, int right) {
        // pick pivot by using mid point
        int pivotIdx = (right + left)/2;        
        int pivot = array[pivotIdx];
        // move pivot to end of array ( to keep it out of the sorting procedure because it will be placed in the correct position at the end)
        array[pivotIdx] = array[right];
        array[right] = pivot;

        // we track a left index holding smallest value compared to pivot and right index holding a value greater than pivot
        int leftPointerIdx = 0;
        int rightPointerIdx = right - 1; // we -1 because we want to skip the last value in array ( because we swapped )
        
        // now we sort everything according to the value of the current pivotIdx
        while (leftPointerIdx < rightPointerIdx) {        
            while(leftPointerIdx <= rightPointerIdx && array[leftPointerIdx] <= pivot) { // we keep shifting the left pointer to the right if the value there is smaller or equal to pivot
                leftPointerIdx += 1;
            }
            while(leftPointerIdx <= rightPointerIdx && array[rightPointerIdx] >= pivot) { // we keep shifting the right pointer to the left if the value there is larger or equal to pivot
                rightPointerIdx -= 1;
            }
            
            // here, we have a value of the left side larger than pivot AND a value on the right side smaller than pivot. Because this is the case, we swap 
            if (leftPointerIdx < rightPointerIdx) {
                int temp = array[leftPointerIdx];
                array[leftPointerIdx] = array[rightPointerIdx];
                array[rightPointerIdx] = temp;

                // for(int j=0; j<10; j++) {
                //     printf("(%i: %i),", j, array[j]);
                // }
                // printf("[swapped indices: %i, %i]\n", tempLeftIdx, tempRightIdx); 
            }        
        }
        // then, we swap back the pivot to the left pointer ( which will be the position that this pivot value will be correctly sorted )
        if (array[right] < array[leftPointerIdx]) {
            int temp = array[right];
            array[right] = array[leftPointerIdx];
            array[leftPointerIdx] = temp;
        }
        // for(int j=0; j<10; j++) {
        //     printf("(%i: %i),", j, array[j]);
        // }
        // printf("[returned pivot indices: %i, %i, %i]\n", pivotIdx, tempLeftIdx, right); 

        return leftPointerIdx; // we return tempLeftIndex because that is the index of where the new pivot value is 
    }

    int partitionStable(int* array, int left, int right) {
        int n = right-left+1; // we need to allocate a new array that is the same size as what we are looping through because the pivot at worse case may be the smallest value in this section we are sorting.
        int rightSideArray[n]; // right side array to temporarily store values that are greater than pivot value    
        
        int pivotIdx = (right + left)/2; // pick pivot by using mid point
        int pivot = array[pivotIdx];
        
        int leftIdx = left;
        int rightIdx = 1; // we start at 1 because 0 index will always be the pivot value
        
        for(int i=left; i<right + 1; i++) { // added a +1 here because the initial right value is at n-1
            if (i == pivotIdx) rightSideArray[0] = array[i]; // this means we have hit the pivot, so we set the first value in right array to be the value
            else if(array[i] <= pivot) { // we move values smaller than pivot to left side of array             
                array[leftIdx] = array[i];
                leftIdx += 1;
            }
            else if (array[i] == pivot && i < pivotIdx) { // we move values equal to pivot but not at the pivot itself. this together with the sequential loop makes the algorithm stable
                array[leftIdx] = array[i];
                leftIdx += 1;
            }
            else { // we assign value to the newly created right array b.
                rightSideArray[rightIdx] = array[i];
                rightIdx += 1;
            }    
        }

        // now we reassign every value in b back to a.
        for (int i=0; i<rightIdx; i++) { // we just need to loop through until rightIdx because that is how many values were set to the right array 
            array[leftIdx] = rightSideArray[i];
            leftIdx += 1;
        }
        // then we return the new index of our pivot in this array.
        return right - rightIdx + 1;
    }

    int partitionLomuto(int* array, int left, int right) {      
        int pivot = array[right];

        int tempPivotIndex = left - 1;
        
        for (int i=left; i<right; i++) {
            if (array[i] <= pivot) {
                tempPivotIndex += 1;
                int temp = array[i];
                array[i] = array[tempPivotIndex];
                array[tempPivotIndex] = temp;
            }
        }

        tempPivotIndex += 1;
        if (array[right] < array[tempPivotIndex]) {
            int temp = array[right];
            array[right] = array[tempPivotIndex];
            array[tempPivotIndex] = temp;
        }

        return tempPivotIndex;
    }

    int* quick_sort(int* array, int left, int right) {
        if (left < right) {
            // int partitionIdx = partitionHoare(array, left, right);
            // int partitionIdx = partitionStable(array, left, right);
            int partitionIdx = partitionLomuto(array, left, right);
            array = quick_sort(array, left, partitionIdx-1);
            array = quick_sort(array, partitionIdx+1, right);
        }
        return array;
    }

    void mergeTopdown(int* array, int left, int mid, int right) {
        // create a new array of size right-left + 1
        int size = right-left+1;
        int tempArray[size];

        // keep track of a left and right pointer
        int leftPointerIdx = left;
        int middlePointerIdx = mid + 1;

        // loop through from 0 to size of tempArray
        for(int i=0; i <size; i++) {            
            if (middlePointerIdx >= left + size) { // we check if mid pointer idx is already larger than range, if so we can automatically assign the left pointer idx into the rest of the array in order ( because they would have been sorted )
                tempArray[i] = array[leftPointerIdx];
                leftPointerIdx += 1;                
            } else if (leftPointerIdx >= mid + 1) { // we check if left pointer idx is already larger than mid point, if so we can automatically assign the mid pointer idx into the rest of the array in order ( because they would have been sorted )
                tempArray[i] = array[middlePointerIdx];
                middlePointerIdx += 1;
            }
            else {
                // check current value with middle, if it's smaller we assign to left index of new array else assign to middle index            
                if (array[leftPointerIdx] <= array[middlePointerIdx]) {
                    tempArray[i] = array[leftPointerIdx];
                    leftPointerIdx += 1;
                } else {
                    tempArray[i] = array[middlePointerIdx];                    
                    middlePointerIdx += 1;
                }               
            }       
        }

        // now we copy everything from tempArray back to array
        int j = 0;
        for(int i=left; i<=right; i++) {
            array[i] = tempArray[j];
            j += 1;
        }
    }

    int* merge_sort(int* array, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            array = merge_sort(array, left, mid);
            array = merge_sort(array, mid+1, right);
            mergeTopdown(array, left, mid, right);
        }
        return array;
    }

    int* counting_sort(int* array, int length, int bucketSize) {
        int b[bucketSize];
        // we initialize buckets to be 0;
        for(int i=0; i<bucketSize; i++) {
            b[i] = 0;
        }
        
        // we loop through array and add a count to a bucket when value is in the array
        for(int i=0; i<length; i++) {
            b[array[i]] += 1;
        }

        // we then loop through all the buckets and reassign them back to array for proper sort order
        int idx = 0;
        for(int i=0; i<bucketSize; i++) {
            int v = b[i];
            while (v > 0) {
                array[idx] = i;
                idx += 1;
                v -= 1; 
            }
        }

        return array;    
    }
}