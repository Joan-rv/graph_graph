#include "graph.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool push_empty_node(struct graph_s *graph, size_t *capacity) {
    static const struct graph_node_s new_node = {
        .adjacencies = NULL,
        .adjacencies_size = 0,
    };

    if (graph->nodes_size >= *capacity) {
        if (*capacity == 0)
            *capacity = 1;
        *capacity *= 2;
        struct graph_node_s *new_nodes =
            realloc(graph->nodes, *capacity * sizeof(struct graph_node_s));
        if (!new_nodes) {
            perror("realloc");
            return false;
        }
        graph->nodes = new_nodes;
    }

    graph->nodes[graph->nodes_size] = new_node;
    graph->nodes_size++;
    return true;
}

bool push_adjacency(struct graph_node_s *node, size_t *capacity,
                    size_t adjacency) {
    if (node->adjacencies_size >= *capacity) {
        if (*capacity == 0)
            *capacity = 1;
        *capacity *= 2;
        size_t *new_adjacencies =
            realloc(node->adjacencies, *capacity * sizeof(size_t));
        if (!new_adjacencies) {
            perror("realloc");
            return false;
        }
        node->adjacencies = new_adjacencies;
    }

    node->adjacencies[node->adjacencies_size] = adjacency;
    node->adjacencies_size++;
    return true;
}

int edge_cmp(const void *pa, const void *pb) {
    size_t a = *(const size_t *)pa;
    size_t b = *(const size_t *)pb;
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}

bool graph_validate(const struct graph_s graph) {
    for (size_t i = 0; i < graph.nodes_size; i++) {
        const struct graph_node_s node = graph.nodes[i];
        for (size_t j = 0; j < node.adjacencies_size; j++) {
            if (node.adjacencies[j] == i ||
                node.adjacencies[j] >= graph.nodes_size)
                return false;
        }
    }
    return true;
}

struct graph_s read_graph(FILE *stream) {
    struct graph_s graph = {.nodes = NULL, .nodes_size = 0};
    size_t graph_capacity = 0;
    char *line = NULL;
    size_t line_size;

    while (getline(&line, &line_size, stream) != -1) {
        if (!push_empty_node(&graph, &graph_capacity)) {
            goto error;
        }

        size_t node_capacity = 0;
        char *adjacency_str = strtok(line, " ");
        struct graph_node_s *node = &graph.nodes[graph.nodes_size - 1];
        while (adjacency_str) {
            size_t adjacency_idx = strtoul(adjacency_str, NULL, 0);
            if (adjacency_idx == ULONG_MAX) {
                perror("strtoul");
                goto error;
            }

            if (!push_adjacency(node, &node_capacity, adjacency_idx)) {
                goto error;
            }
            adjacency_str = strtok(NULL, " ");
        }

        size_t *new_adjacencies =
            realloc(node->adjacencies, node->adjacencies_size * sizeof(size_t));
        if (new_adjacencies == NULL)
            goto error;
        node->adjacencies = new_adjacencies;
        qsort(node->adjacencies, node->adjacencies_size, sizeof(size_t),
              &edge_cmp);
    }

    if (ferror(stream)) {
        perror("getline");
        goto error;
    }

    if (!graph_validate(graph)) {
        fprintf(stderr, "Invalid graph\n");
        goto error;
    }

    struct graph_node_s *new_nodes =
        realloc(graph.nodes, graph.nodes_size * sizeof(struct graph_node_s));
    if (new_nodes == NULL)
        goto error;
    graph.nodes = new_nodes;

    free(line);
    return graph;

error:
    free(line);
    free_graph(graph);
    graph.nodes = NULL;
    return graph;
}

void print_graph(const struct graph_s graph) {
    for (size_t i = 0; i < graph.nodes_size; i++) {
        struct graph_node_s *node = &graph.nodes[i];
        size_t j;
        for (j = 0; j + 1 < node->adjacencies_size; j++) {
            printf("%lu ", node->adjacencies[j]);
        }
        if (j < node->adjacencies_size) {
            printf("%lu", node->adjacencies[j]);
        }
        printf("\n");
    }
}

void free_graph(struct graph_s graph) {
    for (size_t i = 0; i < graph.nodes_size; i++) {
        free(graph.nodes[i].adjacencies);
    }
    free(graph.nodes);
}
