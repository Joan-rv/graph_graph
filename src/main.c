#include "graph.h"
#include "graph_draw.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const int screen_width = 800;
    const int screen_height = 450;

    struct graph_s graph;
    if (argc == 1) {
        graph = read_graph(stdin);
    } else if (argc == 2) {
        FILE *i_file = fopen(argv[1], "r");
        if (i_file == NULL) {
            perror("Could not open file");
            return -1;
        }
        graph = read_graph(i_file);
        fclose(i_file);
    } else if (argc > 2) {
        printf("Usage:\n%s: [file]\n", argv[0]);
        return -1;
    }
    if (graph.nodes == NULL) {
        return -1;
    }
    print_graph(graph);

    Vector2 *node_positions =
        initialize_positions(graph, screen_width, screen_height);
    if (node_positions == NULL) {
        free_graph(graph);
        return -1;
    }

    InitWindow(screen_width, screen_height, "graph_graph");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        update_graph_positions(graph, node_positions, dt);
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            draw_graph(graph, node_positions);
        }
        EndDrawing();
    }

    CloseWindow();
    free(node_positions);
    free_graph(graph);

    return 0;
}
