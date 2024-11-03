#include "kvs.h"

// Skip List의 모든 노드를 해제하는 함수
int close(kvs_t* kvs) {
    if (!kvs) return -1;

    node_t* current = kvs->header->forward[0];
    while (current) {
        node_t* temp = current;
        current = current->forward[0];
        free(temp->value);
        free(temp->forward);
        free(temp);
    }
    free(kvs->header->forward);
    free(kvs->header);
    free(kvs);

    return 0;
}

