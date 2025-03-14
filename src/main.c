#include "graph.h"
#include <raylib.h>
#include <stdio.h>

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

    InitWindow(screen_width, screen_height, "graph_graph");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("Hello world", 340, 200, 20, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    free_graph(graph);

    return 0;
}
