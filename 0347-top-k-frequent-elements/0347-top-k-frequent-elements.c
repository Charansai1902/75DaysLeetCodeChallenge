int compare(const void* a, const void* b) {
    return ((int*)b)[1] - ((int*)a)[1];
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int** freqMap = (int**)malloc(numsSize * sizeof(int*));
    int uniqueCount = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (freqMap[j][0] == nums[i]) {
                freqMap[j][1]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freqMap[uniqueCount] = (int*)malloc(2 * sizeof(int));
            freqMap[uniqueCount][0] = nums[i];
            freqMap[uniqueCount][1] = 1;
            uniqueCount++;
        }
    }
    
    for (int i = 0; i < uniqueCount - 1; i++) {
        for (int j = i + 1; j < uniqueCount; j++) {
            if (freqMap[j][1] > freqMap[i][1]) {
                int* temp = freqMap[i];
                freqMap[i] = freqMap[j];
                freqMap[j] = temp;
            }
        }
    }
    
    int* result = (int*)malloc(k * sizeof(int));
    *returnSize = k;
    
    for (int i = 0; i < k; i++) {
        result[i] = freqMap[i][0];
    }
    
    for (int i = 0; i < uniqueCount; i++) {
        free(freqMap[i]);
    }
    free(freqMap);
    
    return result;
}