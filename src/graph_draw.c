#include "graph_draw.h"
#include <stdlib.h>
#include <time.h>

Vector2 *initialize_positions(struct graph_s graph, int width, int height) {
    Vector2 *node_positions =
        malloc(graph.nodes_size * sizeof(struct graph_node_s));
    if (node_positions == NULL) {
        perror("malloc");
        return NULL;
    }

    srand(time(NULL));
    for (size_t i = 0; i < graph.nodes_size; i++) {
        node_positions[i].x = rand() % width;
        node_positions[i].y = rand() % height;
    }

    return node_positions;
}

void draw_graph(struct graph_s graph, Vector2 *positions) {
    for (size_t i = 0; i < graph.nodes_size; i++) {
        DrawCircleV(positions[i], 10.0f, RED);
        struct graph_node_s *node = &graph.nodes[i];
        for (size_t j = 0; j < node->adjacencies_size; j++) {
            DrawLineV(positions[i], positions[node->adjacencies[j]], RED);
        }
    }
}
