#include <stdio.h>
#include <stdlib.h>

int main() {
    int R, C;

    if (scanf("%d %d", &R, &C) != 2) {
        fprintf(stderr, "Error: invalid input");
        return 1;
    }

    char** arr = (char**)malloc(sizeof(char*) * R);
    if (arr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < R; i++) {
        arr[i] = (char*)malloc(sizeof(char) * C);
        if (arr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            fprintf(stderr, "Error: Failed to allocate memory");
            return 1;
        }
        
    }

    return 0;
}