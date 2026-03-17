int compare(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

char* getSortedKey(char* str) {
    int len = strlen(str);
    char* key = (char*)malloc((len + 1) * sizeof(char));
    strcpy(key, str);
    qsort(key, len, sizeof(char), compare);
    return key;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    char** keys = (char**)malloc(strsSize * sizeof(char*));
    int* groupIndex = (int*)malloc(strsSize * sizeof(int));
    int groupCount = 0;
    
    for (int i = 0; i < strsSize; i++) {
        keys[i] = getSortedKey(strs[i]);
        groupIndex[i] = -1;
    }
    
    for (int i = 0; i < strsSize; i++) {
        if (groupIndex[i] == -1) {
            groupIndex[i] = groupCount;
            for (int j = i + 1; j < strsSize; j++) {
                if (groupIndex[j] == -1 && strcmp(keys[i], keys[j]) == 0) {
                    groupIndex[j] = groupCount;
                }
            }
            groupCount++;
        }
    }
    
    char*** result = (char***)malloc(groupCount * sizeof(char**));
    *returnColumnSizes = (int*)malloc(groupCount * sizeof(int));
    *returnSize = groupCount;
    
    for (int i = 0; i < groupCount; i++) {
        (*returnColumnSizes)[i] = 0;
    }
    
    for (int i = 0; i < strsSize; i++) {
        (*returnColumnSizes)[groupIndex[i]]++;
    }
    
    int* currentIndex = (int*)calloc(groupCount, sizeof(int));
    for (int i = 0; i < groupCount; i++) {
        result[i] = (char**)malloc((*returnColumnSizes)[i] * sizeof(char*));
    }
    
    for (int i = 0; i < strsSize; i++) {
        int group = groupIndex[i];
        result[group][currentIndex[group]] = strs[i];
        currentIndex[group]++;
    }
    
    for (int i = 0; i < strsSize; i++) {
        free(keys[i]);
    }
    free(keys);
    free(groupIndex);
    free(currentIndex);
    
    return result;
}