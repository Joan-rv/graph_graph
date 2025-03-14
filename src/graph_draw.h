#ifndef GRAPH_DRAW_H
#define GRAPH_DRAW_H

#include "graph.h"
#include <raylib.h>

Vector2 *initialize_positions(struct graph_s graph, int width, int height);
void draw_graph(struct graph_s graph, Vector2 *positions);
void update_graph_positions(struct graph_s graph, Vector2 *positions, float dt);

#endif
