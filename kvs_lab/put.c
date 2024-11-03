#include "kvs.h"

static int random_level() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

int put(kvs_t* kvs, const char* key, const char* value) {
    node_t* update[MAX_LEVEL + 1];
    node_t* current = kvs->header;


    for (int i = kvs->level; i >= 0; i--) {
        while (current->forward[i] && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];


    if (current && strcmp(current->key, key) == 0) {
        free(current->value);
        current->value = strdup(value);
        return 0;
    }


    int level = random_level();
    if (level > kvs->level) {
        for (int i = kvs->level + 1; i <= level; i++) {
            update[i] = kvs->header;
        }
        kvs->level = level;
    }

    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    strcpy(new_node->key, key);
    new_node->value = strdup(value);
    new_node->forward = (node_t**)malloc(sizeof(node_t*) * (level + 1));

    for (int i = 0; i <= level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }

    kvs->items++;
    return 0;
}

