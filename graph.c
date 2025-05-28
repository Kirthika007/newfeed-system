#include "graph.h"
#include <stdlib.h>

Node* create_node(int id, char type) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->type = type;
    node->edges = NULL;
    return node;
}

void add_edge(Node *src, Node *dest, int weight) {
    Edge *edge = (Edge*)malloc(sizeof(Edge));
    edge->weight = weight;
    edge->target = dest;
    edge->next = src->edges;
    src->edges = edge;
}
