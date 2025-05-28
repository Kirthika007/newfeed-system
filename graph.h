#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int id;
    char type;
    struct Edge *edges;
} Node;

typedef struct Edge {
    int weight;
    struct Node *target;
    struct Edge *next;
} Edge;

Node* create_node(int id, char type);
void add_edge(Node *src, Node *dest, int weight);

#endif
