#include <stddef.h>
#include <stdio.h>

struct graph_node_s {
    size_t *adjacencies;
    size_t adjacencies_size;
};

struct graph_s {
    struct graph_node_s *nodes;
    size_t nodes_size;
};

struct graph_s read_graph(FILE *stream);
void print_graph(struct graph_s graph);
void free_graph(struct graph_s graph);
