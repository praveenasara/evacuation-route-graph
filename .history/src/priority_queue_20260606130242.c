#include "priority_queue.h"
#include <stdlib.h>

PriorityQueue *pq_create(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->data = malloc(capacity * sizeof(PQNode));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

static void swap(PQNode *a, PQNode *b) {
    PQNode tmp = *a; *a = *b; *b = tmp;
}

void pq_push(PriorityQueue *pq, int node, double dist) {
    if (pq->size >= pq->capacity) {
        pq->capacity *= 2;
        pq->data = realloc(pq->data, pq->capacity * sizeof(PQNode));
    }
    pq->data[pq->size] = (PQNode){node, dist};
    int i = pq->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->data[parent].dist > pq->data[i].dist) {
            swap(&pq->data[parent], &pq->data[i]);
            i = parent;
        } else break;
    }
}

PQNode pq_pop(PriorityQueue *pq) {
    PQNode top = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    int i = 0;
    while (1) {
        int l = 2*i+1, r = 2*i+2, smallest = i;
        if (l < pq->size && pq->data[l].dist < pq->data[smallest].dist) smallest = l;
        if (r < pq->size && pq->data[r].dist < pq->data[smallest].dist) smallest = r;
        if (smallest == i) break;
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }
    return top;
}

int pq_empty(PriorityQueue *pq) { return pq->size == 0; }

void pq_free(PriorityQueue *pq) { free(pq->data); free(pq); }