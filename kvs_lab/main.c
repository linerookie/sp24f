#include "kvs.h"
#include <stdio.h>
#include <string.h>

int main() {
    kvs_t* kvs = open();
    if (!kvs) {
        printf("Failed to open KVS\n");
        return -1;
    }

    FILE* query_file = fopen("query.dat", "r");
    if (!query_file) {
        printf("Failed to open query.dat\n");
        close(kvs);
        return -1;
    }

    FILE* answer_file = fopen("answer.dat", "w");
    if (!answer_file) {
        printf("Failed to create answer.dat\n");
        fclose(query_file);
        close(kvs);
        return -1;
    }

    char command[10], key[100], value[100];
    while (fscanf(query_file, "%9[^,],%99[^,],%99[^\n]\n", command, key, value) != EOF) {
        if (strcmp(command, "get") == 0) {
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "%s\n", result);
                free(result);
            } else {
                fprintf(answer_file, "-1\n");  // 키가 없으면 -1 기록
            }
        } else if (strcmp(command, "set") == 0) {
            put(kvs, key, value);
        }
    }

    fclose(query_file);
    fclose(answer_file);
    close(kvs);
    return 0;
}

