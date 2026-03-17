int compare(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}
bool isAnagram(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);   
    if (len_s != len_t) {
        return false;
    }
    qsort(s, len_s, sizeof(char), compare);
    qsort(t, len_t, sizeof(char), compare);
    return strcmp(s, t) == 0;
}