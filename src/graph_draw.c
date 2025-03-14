#include "graph_draw.h"
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

#define EDGE_LEN 100.0f
#define SPRING_STRENGTH 1.0f

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

void update_graph_positions(struct graph_s graph, Vector2 *positions,
                            float dt) {
    for (size_t i = 0; i < graph.nodes_size; i++) {
        struct graph_node_s *node = &graph.nodes[i];
        for (size_t j = 0; j < node->adjacencies_size; j++) {
            Vector2 pos1 = positions[i];
            Vector2 pos2 = positions[node->adjacencies[j]];
            float dist = Vector2Distance(pos1, pos2);
            float delta_dist = dist - EDGE_LEN;
            Vector2 move_normal = Vector2Normalize(Vector2Subtract(pos2, pos1));
            float move_scale = dt * delta_dist * SPRING_STRENGTH;
            positions[i] =
                Vector2Add(pos1, Vector2Scale(move_normal, move_scale));
        }
    }
}
