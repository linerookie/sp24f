#ifndef KVS_H
#define KVS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LEVEL 6 // 최대 레벨 설정

typedef struct node {
    char key[100];
    char* value;
    struct node** forward; // 각 레벨의 다음 노드를 가리키는 다차원 포인터
} node_t;

typedef struct kvs {
    int level; // 현재 Skip List의 최대 레벨
    int items; // 데이터 개수
    node_t* header; // 헤더 노드
} kvs_t;

kvs_t* open();
int close(kvs_t* kvs);
int put(kvs_t* kvs, const char* key, const char* value);
char* get(kvs_t* kvs, const char* key);

#endif

