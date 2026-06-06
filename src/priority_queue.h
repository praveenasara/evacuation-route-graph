#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
    int   node;
    double dist;
} PQNode;

typedef struct {
    PQNode *data;
    int     size;
    int     capacity;
} PriorityQueue;

PriorityQueue *pq_create(int capacity);
void           pq_push(PriorityQueue *pq, int node, double dist);
PQNode         pq_pop(PriorityQueue *pq);
int            pq_empty(PriorityQueue *pq);
void           pq_free(PriorityQueue *pq);

#endif